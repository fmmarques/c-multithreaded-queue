#if !defined(ABSTRACT_QUEUE_OBSERVER_H)
#  define ABSTRACT_QUEUE_OBSERVER_H

#include <condition_variable>
#include <vector>
#include <memory>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "queue_observer.h"

template< class element_t >
class abstract_queue_observer: queue_observer< element_t > {
public:
  abstract_queue_observer(): 
    _vElements() 
  {}
  
  abstract_queue_observer(abstract_queue_observer< element_t > && rval): 
    _vElements(std::move(rval._vElements)) 
  {}

  ~abstract_queue_observer() {}

  abstract_queue_observer< element_t >& operator=(abstract_queue_observer< element_t >&& rval) { 
    _vElements = move( rval._vElements ); 
  }

  void notify( const std::vector< element_t >& aData ) {

    std::unique_lock<std::mutex> uLock(_mxMutex,std::defer_lock);
    
    uLock.lock();
    for( element_t element : aData ) 
      _vElements.push_back( element );
    _condHasElements.notify_one();

  }

  void run() {
    std::unique_lock<std::mutex> uLock(_mxMutex,std::defer_lock);
    
    uLock.lock();
    _condHasElements.wait(uLock);
    std::for_each( _vElements.begin(), _vElements.end(), std::ostream_iterator<element_t>(std::cout, " "));
    _vElements.clear();
    uLock.unlock();
  }

private:
  std::vector< element_t > _vElements;
  std::condition_variable _condHasElements;
  std::mutex _mxMutex;
};

#endif


