cmake_minimum_required(VERSION 3.8)

project(DataComparison LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("lib")
add_subdirectory("core")
add_subdirectory("tests")

set(headers

)

set(sources

)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE core)
