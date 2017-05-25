#if !defined(MOCK_QUEUE_OBSERVER)
#  define MOCK_QUEUE_OBSERVER

#include <gmock/gmock.h>
#include <queue_observer.h>

template < class element_t >
class mock_queue_observer: public virtual queue_observer< element_t >
{

public:
  MOCK_METHOD1_T(notify, void(std::vector< element_t >& data_set));
  MOCK_METHOD0_T(run, void());
};

#endif
