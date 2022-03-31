include_directories(include)
find_package(FLEX)

include_directories(include)

FLEX_TARGET(Scanner src/Lexer.l ${CMAKE_BINARY_DIR}/flex_out.cpp)
include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(Tests)
