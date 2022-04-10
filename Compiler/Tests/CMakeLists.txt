find_package(GTest)
if (NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif ()

enable_testing()

set(LEXER_SRCS_PATH "../Lexer/sources/")
set(LEXER_INCL_PATH "../Lexer/includes/")

FLEX_TARGET(Scanner ${LEXER_SRCS_PATH}/Lexer.l ${CMAKE_BINARY_DIR}/flex_out.cpp)
add_executable(lexer_tests
        test_lexer.cpp
        ${LEXER_SRCS_PATH}/Lexer.cpp
        ${FLEX_Scanner_OUTPUTS}
)
target_include_directories(lexer_tests PUBLIC ${LEXER_INCL_PATH})
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
add_dependencies(run_lexer_tests lexer_tests)

if (ADD_SANITIZERS)
    target_compile_options(lexer_tests PUBLIC -fsanitize=address -g)
    set_target_properties(lexer_tests PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()