cmake_minimum_required(VERSION 3.16)
project(VirtualMachine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB_RECURSE ALL_CPP_FILES ./*.cpp)
add_subdirectory(Compiler)

add_custom_target(
        clang-format
        COMMAND clang-format
        -i
        ${ALL_CPP_FILES}
)

if (ADD_CLANG_TIDY)
    message("Build with clang-tidy")
    set(CMAKE_CXX_CLANG_TIDY
            clang-tidy
            --format-style=file
            --header-filter=*.h
            )
endif ()