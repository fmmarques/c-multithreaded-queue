#if !defined(TESTS_QUEUE_H)
#  define TESTS_QUEUE_H

#include <gtest/gtest.h>
#include <mock_queue_observer.h>
#include <observable_queue.h>

namespace {

class test_observable_queue : public ::testing::Test {
protected:
  observable_queue< std::shared_ptr< char* >,
                    mock_queue_observer< std::shared_ptr< char * > > > _qSubject;
  std::shared_ptr< char * > _spBuffer;
  std::shared_ptr< mock_queue_observer< std::shared_ptr< char * > > > _spObserver;
  std::thread _tQueueRun;
protected:
  test_observable_queue();
  virtual ~test_observable_queue();

  virtual void SetUp();
 
};

}

#endif
