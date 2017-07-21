cmake_minimum_required (VERSION 2.6)
project (elements)

include_directories("/usr/local/include/")

set(CMAKE_C_FLAGS "-std=c99 -g")

set(SOURCE_FILES
  skiplist.h
  skiplist.c)

set(TEST_FILES
  skiplist_test.c)

AUX_SOURCE_DIRECTORY(src SOURCE_FILES)

add_library(skiplist STATIC ${SOURCE_FILES})

add_executable(runTests
  skiplist_test.c)

target_link_libraries(runTests skiplist)
