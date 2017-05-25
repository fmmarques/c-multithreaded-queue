#if !defined(QUEUE_OBSERVER_H)
#  define QUEUE_OBSERVER_H

#include <memory>
#include <vector>

template < class element_t >
struct queue_observer : public std::enable_shared_from_this< queue_observer< element_t > > 
{
  virtual void notify( std::vector< element_t >& data_set ) = 0;
  virtual void run() = 0;
  virtual ~queue_observer() {}
};

#endif
