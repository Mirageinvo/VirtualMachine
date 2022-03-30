include_directories(include)
find_package(FLEX)

include_directories(include)
FLEX_TARGET(Scanner src/Lexer.l ${CMAKE_CURRENT_BINARY_DIR}/flex_out.cpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(Lexer
        src/Lexer.cpp
        ${FLEX_Scanner_OUTPUTS}
        )
target_link_libraries(Lexer ${FLEX_LIBRARIES})
