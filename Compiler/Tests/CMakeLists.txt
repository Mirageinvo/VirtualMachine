include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(SRCS_PATH "../src/")
set(INCL_PATH "../include/")

FLEX_TARGET(Scanner ${SRCS_PATH}/Lexer.l ${CMAKE_BINARY_DIR}/flex_out.cpp)
add_executable(lexer_tests
        test_lexer.cpp
        ${SRCS_PATH}/Lexer.cpp
        ${FLEX_Scanner_OUTPUTS}
)
target_link_libraries(lexer_tests PUBLIC gtest_main ${FLEX_LIBRARIES})
target_include_directories(lexer_tests PUBLIC ${INCL_PATH})

include(GoogleTest)
gtest_discover_tests(lexer_tests)

add_custom_target(
    run_lexer_tests
    COMMENT "Running tests for RBTree"
    COMMAND ./lexer_tests
)
add_dependencies(run_lexer_tests lexer_tests)

if (ADD_SANITIZERS)
    target_compile_options(lexer_tests PUBLIC -fsanitize=address -g)
    set_target_properties(lexer_tests PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()