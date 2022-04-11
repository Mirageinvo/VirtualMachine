cmake_minimum_required(VERSION 3.16)
project(VirtualMachine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB_RECURSE ALL_VM_FILES *.cpp *.h)

add_custom_target(
        clang-format
        COMMAND clang-format
        -i
        ${ALL_VM_FILES}
)

if (ADD_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY
            clang-tidy
            --format-style=file
            --header-filter=*.h
        )
endif ()

#---------------------------------------

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(LEXER_INCL "Compiler/Lexer/includes")
set(LEXER_SRCS "Compiler/Lexer/sources")
set(PARSER_INCL "Compiler/Parser/includes")
set(PARSER_SRCS "Compiler/Parser/sources")

if (NOT DEFINED GRAMMAR)
    set(GRAMMAR "${PARSER_SRCS}/grammar.y" CACHE STRING "file with grammar" FORCE)
endif()

flex_target(scanner
    ${LEXER_SRCS}/lexer.l
    ${CMAKE_BINARY_DIR}/flex_out.cpp
)

bison_target(parser
    ${GRAMMAR}
    ${CMAKE_BINARY_DIR}/bison_out.cpp
    COMPILE_FLAGS "--defines=${CMAKE_BINARY_DIR}/grammar.tab.hh"
)

add_flex_bison_dependency(scanner parser)

add_executable(made_prog
  main.cpp
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
)

target_compile_features(made_prog PRIVATE cxx_std_20)
target_include_directories(made_prog PRIVATE ${LEXER_INCL})
target_include_directories(made_prog PRIVATE ${PARSER_INCL})
target_include_directories(made_prog PRIVATE ${CMAKE_CURRENT_DIR})

#---------------------------------------
#[[
find_package(GTest)
if (NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif ()

enable_testing()

add_executable(lexer_tests
        Compiler/tests/test_lexer.cpp
        ${LEXER_SRCS}/lexer.cpp
        ${FLEX_Scanner_OUTPUTS}
)
target_include_directories(lexer_tests PUBLIC ${LEXER_INCL})
if (GTest_FOUND)
    target_link_libraries(lexer_tests PUBLIC GTest::GTest GTest::Main ${FLEX_LIBRARIES})
else ()
    target_link_libraries(lexer_tests PUBLIC gtest_main ${FLEX_LIBRARIES})
endif ()

include(GoogleTest)
gtest_discover_tests(lexer_tests)

add_custom_target(
    run_lexer_tests
    COMMENT "Running tests for Lexer"
    COMMAND ./lexer_tests
)
add_dependencies(run_lexer_tests lexer_tests)]]