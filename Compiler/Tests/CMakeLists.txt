message("Include Compile testing")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

FLEX_TARGET(Scanner ../src/Lexer.l ${CMAKE_BINARY_DIR}/flex_out.cpp)
include_directories(${CMAKE_BINARY_DIR})
add_executable(Lexer_tests
        test_lexer.cpp
        ../src/Lexer.cpp
        ${FLEX_Scanner_OUTPUTS}
        )
target_link_libraries(Lexer_tests PUBLIC GTest::GTest GTest::Main ${FLEX_LIBRARIES})
enable_testing()

if (ADD_SANITIZERS)
    message("Build with sanitizers")

    target_compile_options(Lexer_tests PUBLIC -fsanitize=address -g)
    set_target_properties(Lexer_tests PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()
