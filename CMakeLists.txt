cmake_minimum_required(VERSION 3.15)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

project(fsm_example_c)
set(CMAKE_CXX_STANDARD 98)
add_executable(${PROJECT_NAME} ${EXAMPLES_DIR}/example.c ${INCLUDE_DIR}/finite_state_machine.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

project(fsm_example_cpp)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME} ${EXAMPLES_DIR}/example.cpp ${INCLUDE_DIR}/finite_state_machine.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
