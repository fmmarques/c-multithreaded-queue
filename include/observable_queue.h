#if !defined(OBSERVABLE_QUEUE_H)
#  define OBSERVABLE_QUEUE_H

#include <memory>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include <algorithm>

#include <initializer_list>


#include <queue_observer.h>

template < class observer_t >
struct observable {
  virtual void add( std::shared_ptr< observer_t >& pObserver ) = 0;
  virtual void remove( std::shared_ptr< observer_t >& pObserver ) = 0;

  virtual void run() = 0;
};

template< class element_t,
	  class observer_t = queue_observer< element_t >,
          class container_t = std::vector< element_t >,
          class comparer_t = std::less< element_t > >
class observable_queue : public virtual observable< observer_t > {
private:
  std::mutex _rmMutex; 
  container_t _queue;
  bool _isShutdown;
  std::condition_variable _hasElementsToPopOrShutdown;
  std::vector< std::shared_ptr< observer_t > > _vObservers;
protected:

  void invariant() const {
/*    std::vector< std::shared_ptr< observer < element_t > > >::const_iterator itOverObserversToCompareTo = _vObservers.cbegin();
    while ( _vObservers.cend() != itOverObserversToCompareTo ) {
      assert( std::all_of( itOverObservers, _vObservers.cend(), [&itOverObservers]( std::shared_ptr< observer < element_t > > >::const_iterator& itOverObserversToCompareTo) { 
           return ( *itOverObservers != *itOverObserversToCompareTo ); 
      } ) );
      itOverObservers++;
    } 
*/
  }

public:
  template< class container_tt >
  observable_queue(observable_queue<element_t, container_tt>&& anotherContainer):
    _queue(),
    _isShutdown(false),
    _hasElementsToPopOrShutdown()
  {
    std::unique_lock<std::mutex> _uLock(_rmMutex, std::defer_lock);

    _uLock.lock();
    std::lock_guard<std::recursive_mutex> lExclusiveOverAnotherContainer(std::move(anotherContainer._rmMutex));
    container_tt& input = std::ref(anotherContainer._queue);
    while (input.size() > 0) {
      element_t tmp = std::move(input.top());
      input.pop();
      _queue.emplace(tmp);
    }
    _hasElementsToPopOrShutdown.notify_all();
    invariant();
    _uLock.unlock();
  }

  observable_queue(const std::initializer_list<element_t>& lstListOfElements):
    _queue(),
    _isShutdown(false),
    _hasElementsToPopOrShutdown()
  {
    std::unique_lock<std::mutex> _uLock(_rmMutex, std::defer_lock);

    _uLock.lock();
    auto itList = lstListOfElements.begin();
    comparer_t compare = comparer_t();
    for( auto itList : lstListOfElements ) {
      auto itQueue = _queue.begin();
      while (itQueue != _queue.end() && compare(*itQueue, itList)) {
        itQueue++;
      }
      _queue.emplace(itQueue, itList);
    }
    _hasElementsToPopOrShutdown.notify_all();
    invariant();
    _uLock.unlock();
  }

  observable_queue():
    _queue(),
    _isShutdown(false),
    _hasElementsToPopOrShutdown()
  {} 

  ~observable_queue() {
    invariant();
  }
  
  void push(element_t element) {
    std::unique_lock<std::mutex> _uLock(_rmMutex, std::defer_lock);
    
    _uLock.lock();
    invariant();
    if (_isShutdown)
      throw std::out_of_range( std::string(__PRETTY_FUNCTION__).append(" - the queue was shutdown.") );

    auto itQueue = _queue.begin();

    static comparer_t compare = comparer_t();

    while (itQueue != _queue.end() && compare(*itQueue , element)) {
      itQueue++;
    }

    _queue.emplace( itQueue, std::move(element) );
    _hasElementsToPopOrShutdown.notify_all();

    invariant();
    _uLock.unlock();
  }

  unsigned int size() {
    std::unique_lock<std::mutex> _uLock(_rmMutex, std::defer_lock);
    unsigned int uiResult = 0;
    _uLock.lock();
    invariant();
    uiResult = _queue.size();
    invariant();
    _uLock.unlock();
    return uiResult;
  }

  void shutdown() {
    std::unique_lock<std::mutex> _uLock(_rmMutex, std::defer_lock);
    _uLock.lock();
    invariant();
    _isShutdown = true;
    _hasElementsToPopOrShutdown.notify_all();
    invariant();
    _uLock.unlock();
  }

  bool has_shutdown() {
    bool bResult = false;
    std::unique_lock<std::mutex> _uLock(_rmMutex, std::defer_lock);
    _uLock.lock();
    invariant();
    bResult = _isShutdown;
    _hasElementsToPopOrShutdown.notify_all();
    invariant();
    _uLock.unlock();
    return bResult;
  }


  void add( std::shared_ptr< observer_t >& pObserver ) {
    assert( nullptr != pObserver );
    std::unique_lock<std::mutex> _uLock(_rmMutex, std::defer_lock);
    _uLock.lock();
    invariant();
   
    if ( false == std::all_of( _vObservers.begin(), 
                          _vObservers.end(), 
                          [&pObserver]( std::shared_ptr< observer_t >& anotherObserver ) {  
                             return ( pObserver != anotherObserver );
                          } ) ) {
       throw std::invalid_argument("Duplicated observer"); 
    }
    _vObservers.push_back( pObserver );    

    invariant();
    _uLock.unlock();
  }

  

  void remove( std::shared_ptr< observer_t >& pObserver ) { 
    assert( nullptr != pObserver );
    std::unique_lock<std::mutex> _uLock(_rmMutex, std::defer_lock);
    _uLock.lock();
    invariant();

    auto itOverObservers = std::find(_vObservers.begin(), _vObservers.end(), pObserver);
    if (itOverObservers == _vObservers.end())
      throw std::invalid_argument("No such listener");

    do {
      _vObservers.erase( itOverObservers );
      itOverObservers = std::find(itOverObservers, _vObservers.end(), pObserver);
    } while (itOverObservers != _vObservers.end());

    invariant();
    _uLock.unlock();
  }
  

  void run() {
    bool bContinue = false;
    std::unique_lock<std::mutex> _uLock(_rmMutex, std::defer_lock);
    while ( bContinue ) {
   
      _uLock.lock();
      invariant();

      while (0 == _queue.size() && !_isShutdown) 
        _hasElementsToPopOrShutdown.wait(_uLock);

      if (!_isShutdown) {
        bContinue = false;
        break;
      }

      std::vector< element_t > data( _queue.begin(), _queue.end() );
      std::for_each( _vObservers.begin(), _vObservers.end(), [&data]( std::shared_ptr< observer_t >& pObserver) { 
          pObserver->notify( data );
      });
      
    }
    invariant();
    _uLock.unlock();
  }
};


#endif
