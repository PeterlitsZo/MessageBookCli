# ---[ version info ]----------------------------------------------------------

cmake_minimum_required (VERSION 3.13)


# ---[ project info ]----------------------------------------------------------

project (MessageBookCli)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} --g -O0 -std=c++11 -Wall -ggdb")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -Wall -ggdb")


# ---[ help setting ]----------------------------------------------------------

find_package (PythonInterp 3)

set  (
    ALL_MD_TARGET ${CMAKE_SOURCE_DIR}/src/help/help.h
                  ${CMAKE_SOURCE_DIR}/src/help/HELP.cpp
)

if (PythonInterp_FOUND)
    file (GLOB ALL_MD_FILE ${CMAKE_SOURCE_DIR}/docs/insides/*.md)
    add_custom_target (
        HELP_DOCUMENTS
        DEPENDS ${ALL_MD_TARGET}
        COMMENT "making help source file"
    )
    add_custom_command (
        OUTPUT  ${ALL_MD_TARGET}
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/docs/make_info.py
        DEPENDS ${ALL_MD_FILE}
        COMMENT "making help source file"
    )
endif ()


# ---[ parser settint ]--------------------------------------------------------

find_package (BISON)
find_package (FLEX)

if (BISON_FOUND)
if (FLEX_FOUND)
    # make out parser header and parser source file
    BISON_TARGET (MessageBookCli_parser ./src/parser/parser.y
                  ${CMAKE_SOURCE_DIR}/src/parser/parser.cpp
                  DEFINES_FILE ${CMAKE_SOURCE_DIR}/src/parser/parser.h)
    FLEX_TARGET (MessageBookCli_lexer ./src/parser/parser.l
                 ${CMAKE_SOURCE_DIR}/src/parser/lexer.cpp)
    ADD_FLEX_BISON_DEPENDENCY (MessageBookCli_lexer MessageBookCli_parser)
endif ()
endif ()

set (PARSER_FILES   ${CMAKE_SOURCE_DIR}/src/parser/lexer.cpp
                    ${CMAKE_SOURCE_DIR}/src/parser/parser.cpp
                    ${CMAKE_SOURCE_DIR}/src/parser/interface.cpp
                    ${CMAKE_SOURCE_DIR}/src/parser/idmap.cpp
                    ${CMAKE_SOURCE_DIR}/src/parser/lineno.cpp
)

# ---[ main setting ]----------------------------------------------------------

include_directories (${CMAKE_CURRENT_BINARY_DIR})
aux_source_directory (${CMAKE_SOURCE_DIR}/src             SRC_FILES)
aux_source_directory (${CMAKE_SOURCE_DIR}/src/help        SRC_FILES)
aux_source_directory (${CMAKE_SOURCE_DIR}/include/logging SRC_FILES)

add_executable (
    MessageBookCli ${SRC_FILES} ${PARSER_FILES}
)

if (PythonInterp_FOUND)
    add_dependencies (MessageBookCli HELP_DOCUMENTS)
endif()


# ---[ test setting ]----------------------------------------------------------

find_package (GTest REQUIRED)
find_package (Threads REQUIRED)

if (GTest_FOUND)
if (Threads_FOUND)
    # make test
    aux_source_directory (./src TEST_FILES)
    aux_source_directory (${CMAKE_SOURCE_DIR}/include/logging TEST_FILES)
    list (REMOVE_ITEM TEST_FILES ./src/main.cpp)
    add_executable (Tests ${TEST_FILES} ./test/test.cpp)

    target_link_libraries (Tests ${GTEST_BOTH_LIBRARIES})
    target_link_libraries (Tests ${CMAKE_THREAD_LIBS_INIT})

    enable_testing ()
    add_test (Tests Tests)
endif ()
endif ()


