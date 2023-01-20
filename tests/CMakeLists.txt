cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME tests)

project(${PROJECT_NAME})

find_package(Catch2 3 REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Catch2::Catch2WithMain
  deque
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
add_compile_options(-fsanitize=address -Wall -Werror)