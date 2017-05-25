#if !defined(TESTS_QUEUE_H)
#  define TESTS_QUEUE_H

#include <gtest/gtest.h>
#include <queue.h>

namespace {

class test_queue : public ::testing::Test {
protected:
  queue< std::unique_ptr< char * > > _qUniqSubject;
  queue< std::shared_ptr< char * > > _qSharSubject;

protected:
  test_queue() {}
  virtual ~test_queue() {}

};

}

#endif
