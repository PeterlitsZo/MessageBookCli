# ---[ version info ]----------------------------------------------------------

cmake_minimum_required (VERSION 3.13)


# ---[ project info ]----------------------------------------------------------

project (MessageBookCli)


# ---[ output setting ]--------------------------------------------------------

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
aux_source_directory (./src SRC_FILES)
add_executable (MessageBookCli ${SRC_FILES})


# ---[ test setting ]----------------------------------------------------------

find_package (GTest REQUIRED)
find_package (Threads REQUIRED)

aux_source_directory (./src TEST_FILES)
list (REMOVE_ITEM TEST_FILES ./src/main.cpp)
add_executable (Tests ${TEST_FILES} ./test/test.cpp)

target_link_libraries (Tests ${GTEST_BOTH_LIBRARIES})
target_link_libraries (Tests ${CMAKE_THREAD_LIBS_INIT})

enable_testing ()
add_test (Tests Tests)

