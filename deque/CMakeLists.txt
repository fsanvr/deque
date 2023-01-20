cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME deque)

project(${PROJECT_NAME})

set(PUBLIC_INCLUDES
  include/Deque.hpp
)

set(PRIVATE_SOURCES
  src/Deque.cpp
)

add_library(${PROJECT_NAME} STATIC
  ${PUBLIC_INCLUDES}
  ${PRIVATE_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
#target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PUBLIC src) #костыль, у меня симейк не работает

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
add_compile_options(-fsanitize=address -Wall -Werror)