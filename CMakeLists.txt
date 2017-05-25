cmake_minimum_required(VERSION 2.8)
project(queue CXX)

enable_testing()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)


## Dependency: GTest
find_package(GTest 1)
if(NOT GTEST_FOUND OR NOT ${GTEST_FOUND})
  message(STATUS "  Using included GTest")
  set(GTEST_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/dependencies/gtest/googletest/include ${PROJECT_SOURCE_DIR}/dependencies/gtest/googlemock/include)
  set(GTEST_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/dependencies/gtest/googlemock/gtest/libgtest.a)
  set(GTEST_MAIN_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/dependencies/gtest/googlemock/gtest/libgtest_main.a)
  set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

  set(GMOCK_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/dependencies/gtest/googlemock/libgmock.a)
  set(GMOCK_MAIN_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/dependencies/gtest/googlemock/libgmock_main.a)
  set(GMOCK_BOTH_LIBRARIES ${GMOCK_LIBRARIES} ${GMOCK_MAIN_LIBRARIES})
  cmake_policy(SET CMP0015 NEW)
  add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/gtest)
endif()
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})
set(LIBRARIES ${LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

## Dependency: libpthreads
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(CMAKE_PREFER_PTHREAD_FLAG FALSE)
find_package(Threads)
if(NOT DEFINED CMAKE_USE_PTHREADS_INIT)
  message(WARNING "CMake couldn't find pthreads. Please review pthreads' location in your system.")
  set(CMAKE_THREAD_LIBS_INIT "-lpthread")
endif()
set(LIBRARIES ${LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
set(LINK_FLAGS ${LINK_FLAGS} ${CMAKE_THREAD_LIBS_INIT})

## Include directories
### Define include directories ###
set(INCLUDE_DIRS ${INCLUDE_DIRS} include tests/integration/include tests/unit/include)

include_directories(${INCLUDE_DIRS})

## Link directories ##
### Define link directories and libraries ###
### Include the directories ###
link_directories(${LIBRARY_DIRS})


### Sources ###
set(SOURCE_FILES
  src/queue_observer.cpp
  src/observable_queue.cpp
  src/queue.cpp
)

set(TEST_INTEGRATION_FILES
 ${SOURCE_FILES}

# tests/integration/src/integrity.cpp
)

set(TEST_UNIT_FILES
 ${SOURCE_FILES}

 tests/unit/src/test_queue.cpp
 tests/unit/src/test_observable_queue.cpp
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDART_REQUIRED ON)
add_definitions(-std=c++11 -lrt ${LINK_FLAGS})

add_library(queue MODULE  ${SOURCE_FILES})

add_executable(integration ${TEST_INTEGRATION_FILES} tests/integration/src/integration.cpp )
add_executable(unit ${TEST_UNIT_FILES} tests/unit/src/unit.cpp)

set_target_properties(
  queue integration unit 
  PROPERTIES 
    COMPILE_FLAG "-pg -O3 -Wall -g ${COMPILE_FLAGS}"
    LINK_FLAGS "${LINK_FLAGS}" )

#target_link_libraries(libqueue.so ${LIBRARIES})
target_link_libraries(queue ${LIBRARIES} -lpthread)
target_link_libraries(integration ${LIBRARIES} -lpthread) #${GTEST_BOTH_LIBRARIES})
target_link_libraries(unit ${LIBRARIES})# ${GTEST_BOTH_LIBRARIES})

add_dependencies(integration queue)
#if(NOT GTEST_FOUND)
  add_dependencies(integration gtest gtest_main)
  add_dependencies(unit gtest gtest_main)
#endif()

add_test(integration integrity)
add_test(unit unit)
