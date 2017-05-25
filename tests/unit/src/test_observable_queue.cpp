#include <thread>
#include <memory>
#include <test_observable_queue.h>

test_observable_queue::test_observable_queue():
  _qSubject(),
  _spBuffer(nullptr),
  _tQueueRun(&observable_queue< std::shared_ptr< char* >,
                    mock_queue_observer< std::shared_ptr< char * > > >::run, _qSubject)
{}

test_observable_queue::~test_observable_queue()
{}

void test_observable_queue::SetUp()
{
  _spBuffer = std::make_shared<char *>(new char[10]);
  _spObserver = std::make_shared< mock_queue_observer< std::shared_ptr< char * > > >();
  
}

TEST_F(test_observable_queue, add_and_remove_observer)
{
  ASSERT_NO_THROW( _qSubject.add( _spObserver ) );
  ASSERT_THROW( _qSubject.add( _spObserver ), std::invalid_argument );
  ASSERT_NO_THROW( _qSubject.remove( _spObserver ) );
  ASSERT_THROW( _qSubject.remove(_spObserver), std::invalid_argument );
}

TEST_F(test_observable_queue, push) 
{
  using ::testing::_;
  EXPECT_CALL( *(_spObserver), notify(_));

  ASSERT_NO_THROW( _qSubject.add( _spObserver ) );
  ASSERT_THROW( _qSubject.add( _spObserver ), std::invalid_argument );

  ASSERT_NO_THROW( _qSubject.push( _spBuffer ) );
  
   
  SUCCEED();
}

TEST_F(test_observable_queue, push_and_size) {
}

