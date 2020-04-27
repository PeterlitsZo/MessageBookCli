# ---[ version info ]----------------------------------------------------------

cmake_minimum_required (VERSION 3.13)


# ---[ project info ]----------------------------------------------------------

project (MessageBookCli)


# ---[ parser settint ]--------------------------------------------------------

find_package (BISON)
find_package (FLEX)

BISON_TARGET (MessageBookCli_parser ./src/parser/parser.y
              ${CMAKE_SOURCE_DIR}/src/parser/parser.cpp
              DEFINES_FILE ${CMAKE_SOURCE_DIR}/src/parser/parser.h)
FLEX_TARGET (MessageBookCli_lexer ./src/parser/parser.l
             ${CMAKE_SOURCE_DIR}/src/parser/lexer.cpp)

set (PARSER_FILES ${CMAKE_SOURCE_DIR}/src/parser/lexer.cpp
                  ${CMAKE_SOURCE_DIR}/src/parser/parser.cpp)

ADD_FLEX_BISON_DEPENDENCY(MessageBookCli_lexer MessageBookCli_parser)

# ---[ output setting ]--------------------------------------------------------

include_directories (${CMAKE_CURRENT_BINARY_DIR})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
aux_source_directory (./src SRC_FILES)

add_executable (MessageBookCli ${SRC_FILES} ${PARSER_FILES})


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

