#include <test_queue.h>

#include <memory>
#include <make_unique.h>



TEST_F(test_queue, push_and_pop) {
  std::unique_ptr< char * > obj = std::make_unique< char * >(new char[3000]);
  (*obj)[0]='a';
  _qUniqSubject.push(std::move(obj));
  std::unique_ptr< char * > obj2 = std::move(_qUniqSubject.pop());
  ASSERT_EQ('a',(*obj2)[0]);
  ASSERT_NE('b',(*obj2)[0]);
  SUCCEED();
}

TEST_F(test_queue, push_and_size) {
  std::shared_ptr< char * > spPointer = std::make_shared< char * >( new char[3000] );
  (*spPointer)[0] = 'a';
  
  ASSERT_EQ('a', (*spPointer)[0]);
  ASSERT_NE('\0', (*spPointer)[0]);
  
  _qSharSubject.push( spPointer );
  ASSERT_EQ(1, _qSharSubject.size());
  ASSERT_EQ('a', (*spPointer)[0]);
  ASSERT_EQ((*spPointer)[0], (*_qSharSubject.pop())[0]);
}


