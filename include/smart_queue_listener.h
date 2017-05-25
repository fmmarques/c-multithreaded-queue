#include <iostream>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <vector>

#include <functional>
#include <algorithm>

#include <exception>

#include <memory>

using namespace std;

class empty_container_error: public exception {};


template < class element_t >
struct observer : enable_shared_from_this< observer< element_t > > {
  virtual void notify( array< element_t >& data_set ) = 0;

  virtual void run() = 0;
};

template < class element_t, 
           class observer_t >
struct observable {
  virtual void add( shared_ptr< observer< element_t > >& pObserver ) = 0;
  virtual void erase( shared_ptr< observer< element_t > >& pObserver ) = 0;

  virtual void run() = 0;
};

template < class domain_t = unsigned int,
           class progression_t = unsigned int > 
class range {
public:
  range(domain_t&& start, domain_t&& end, progression_t progression = 1):
    _start{start}, _end{end}, _current{start}, _progression{progression}
  {}

  virtual ~range() {};

  domain_t start() { return _start; }
  domain_t curr()  { return _current; }
  domain_t end()   { return _end; }; 

  domain_t operator++()  { return _current += _progression; }

private:
  domain_t _start;
  domain_t _end;
  domain_t _current;
  unsigned int _progression;  
};

template< class element_t,
          class container_t = std::vector<element_t>,
          class comparer_t = std::less<element_t> >
class observable_queue : public virtual observable< element_t, observer > {
private:
  mutex _rmMutex; 
  container_t _queue;
  bool _isShutdown;
  condition_variable _hasElementsToPopOrShutdown;
  vector< shared_ptr< observer < element_t > > > _vObservers;
protected:

  void invariant() const {
    vector< shared_ptr< observer < element_t > > >::const_iterator itOverObservers = _vObservers.cbegin();
    while ( _vObservers.cend() != itOverObservers ) {
      assert( all_of( itOverObservers, _vObservers.cend(), [&itOverObservers]( shared_ptr< observer < element_t > > >::const_iterator& itOverObserversToCompareTo) { 
           return ( *itOverObservers != *itOverObserversToCompareTo ); 
      } ) );
      itOverObservers++;
    } 
  }

public:
  template< class container_tt >
  observable_queue(queue<element_t, container_tt>&& anotherContainer):
//    _uLock(_rmMutex, std::defer_lock),
    _queue(),
    _isShutdown(false),
    _hasElementsToPopOrShutdown()
  {
    unique_lock<mutex> _uLock(_rmMutex, std::defer_lock);

    _uLock.lock();
    lock_guard<recursive_mutex> lExclusiveOverAnotherContainer(std::move(anotherContainer._rmMutex));
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

  observable_queue(const initializer_list<element_t>& lstListOfElements):
//    _uLock(_rmMutex, std::defer_lock),
    _queue(),
    _isShutdown(false),
    _hasElementsToPopOrShutdown()
  {
    unique_lock<mutex> _uLock(_rmMutex, std::defer_lock);

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

  ~observable_queue() {
    invariant();
  }
  
  void push(element_t element) {
    unique_lock<mutex> _uLock(_rmMutex, std::defer_lock);
    
    _uLock.lock();
    invariant();
    if (_isShutdown)
      throw out_of_range( string(__PRETTY_FUNCTION__).append(" - the queue was shutdown.") );
    auto itQueue = _queue.begin();
    comparer_t compare = comparer_t();
    while (itQueue != _queue.end() && compare(*itQueue , element)) {
      itQueue++;
    }
    _queue.emplace( itQueue, std::move(element) );
    _hasElementsToPopOrShutdown.notify_all();
    invariant();
    _uLock.unlock();
  }

  unsigned int size() {
    unique_lock<mutex> _uLock(_rmMutex, std::defer_lock);
    unsigned int uiResult = 0;
    _uLock.lock();
    invariant();
    uiResult = _queue.size();
    invariant();
    _uLock.unlock();
    return uiResult;
  }

  void shutdown() {
    unique_lock<mutex> _uLock(_rmMutex, std::defer_lock);
    _uLock.lock();
    invariant();
    _isShutdown = true;
    _hasElementsToPopOrShutdown.notify_all();
    invariant();
    _uLock.unlock();
  }

  bool has_shutdown() {
    bool bResult = false;
    unique_lock<mutex> _uLock(_rmMutex, std::defer_lock);
    _uLock.lock();
    invariant();
    bResult = _isShutdown;
    _hasElementsToPopOrShutdown.notify_all();
    invariant();
    _uLock.unlock();
    return bResult;
  }


  void add( shared_ptr< observable >& pObserver ) {
    assert( nullptr != pObserver );
    unique_lock<mutex> _uLock(_rmMutex, std::defer_lock);
    _uLock.lock();
    invariant();
   
    if ( false == all_of( _vObservers.begin(), 
                          _vObservers.end(), 
                          [&pObserver]( shared_ptr< observable >& anotherObserver ) {  
                             return ( pObserver != anotherObserver );
                          } ) ) {
       throw duplicated_element(); 
    }
    _vObservers.push_back( pObserver );    

    invariant();
    _uLock.unlock();
  }

  void erase( shared_ptr< observable >& pObserver ) { 
    assert( nullptr != pObserver );
    unique_lock<mutex> _uLock(_rmMutex, std::defer_lock);
    _uLock.lock();
    invariant();

    auto itOverObservers = _vObservers.find( pObserver );
    while ( itOverObservers != _vObservers.end() ) {
      if ( *itOverObservers == pObserver )
        _vObservers.erase( itOverObservers );
      itOverObservers++;
    }    

    invariant();
    _uLock.unlock();
  }
  

  void run() {
    bool bContinue = false;
    unique_lock<mutex> _uLock(_rmMutex, std::defer_lock);
    while ( bContinue ) {
   
      _uLock.lock();
      invariant();

      while (0 == _queue.size() && !_isShutdown) _hasElementsToPopOrShutdown.wait(_uLock);
      if (!_isShutdown) {
        vector< element_t > data( _queue.begin(), _queue.end()+10 );
        for_all( _vObservers.begin(), _vObservers.end(), [](shared_ptr<observer>& pObserver) { 
          pObserver->notify( data );
        } );
      } else {
        bContinue = false;
      }
    }
    invariant(();
    _uLock.unlock();
  }
};

template< class element_t >
class anObserver : observer< element_t > {
public:
  anObserver(): _vElements() {}
  anObserver(anObserver< element_t > && rval): _vElements(move(rval._vElements)) {}
  ~anObserver() {}

  anObserver< element_t >& operator=(anObserver< element_t >&& rval) { _vElements = move( rval._vElements ); }

  void notify( const array< element_t >& aData ) {
    for( element_t element : aData ) {
      // Do something
    }
  }

  void run() {
  }

private:
  vector< element_t > _vElements;
}


void producer(queue<int>& q) {
  using namespace std;
  try {
    int iInput = 0;
    cout << "Reading ints into queue (hit 0 to stop)." << endl << "next int: " << flush;
    cin >> iInput;
    while (iInput) {
      cout << "producer produced: " << iInput << endl;
      cout << "next int: " << flush;
      q.push(iInput);    
      cin >> iInput;
    }
  } catch( out_of_range& e ) {
    if (q.has_shutdown())
      cout << "Producer has ended." << endl;
  }
}

void consumer(queue<int>& q) {
  using namespace std;
  try {
        

  } catch (out_of_range& e) {
    if (q.has_shutdown())
      cout << "Consumer has ended." << endl;
  }
}

int main() {
  using namespace std;

  observable_thread<int> q{1,2,3};
  thread consumer_thread( &anObserver<int>::run
  thread queue_thread( &observable_thread<int>::run, ref(q) );
  

  queue<int> q{50,20,30};
  thread producer_thread(producer, ref(q));
  thread consumer_thread(consumer, ref(q));

  q.shutdown();
/*  
  cout << q.pop();
  while(q.size() > 0) {
    cout << ", " << q.pop();
  }
  cout << endl << flush;
*/ 
  producer_thread.join();
  consumer_thread.join(); 
}
  
