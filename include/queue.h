#if !defined(QUEUE_H)
#  define QUEUE_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>


using namespace std;



template< class element_t,
          class container_t = std::vector<element_t>,
          class comparer_t = std::less<element_t> >
class queue {
private:
  mutex _rmMutex; 
  container_t _queue;
  bool _isShutdown;
  std::condition_variable _hasElementsToPopOrShutdown;
protected:
  void invariant() const {
    
  }
public:
  template< class container_tt >
  queue(queue<element_t, container_tt>&& anotherContainer):
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

  queue(const initializer_list<element_t>& lstListOfElements):
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

  queue():
    _queue(),
    _isShutdown(false),
    _hasElementsToPopOrShutdown()
  {
    invariant();
  }

  ~queue() {
    invariant();
  }
  
  element_t pop() {
    unique_lock<mutex> _uLock(_rmMutex, std::defer_lock);
    
    element_t result;
    _uLock.lock();
    while(0 == _queue.size()) _hasElementsToPopOrShutdown.wait(_uLock);
    if (_isShutdown)
      throw out_of_range( string(__PRETTY_FUNCTION__).append(" - the queue was shutdown.") );
    invariant();
    result = std::move(_queue.front());
    _queue.erase( _queue.begin() );
    invariant();
    _uLock.unlock();
    return result;
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

};

#endif
/*
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
    while (q.size() > 0) {    
      cout << "consumer consumed: " << q.pop() << endl << flush;
    }
  } catch (out_of_range& e) {
    if (q.has_shutdown())
      cout << "Consumer has ended." << endl;
  }
}

int main() {
  using namespace std;


  queue<int> q{50,20,30};
  thread producer_thread(producer, ref(q));
  thread consumer_thread(consumer, ref(q));

  q.shutdown();
*//*  
  cout << q.pop();
  while(q.size() > 0) {
    cout << ", " << q.pop();
  }
  cout << endl << flush;
*//* 
  producer_thread.join();
  consumer_thread.join(); 
}
*/
