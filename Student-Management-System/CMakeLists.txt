cmake_minimum_required(VERSION 3.16)

project(StudentManagementSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(student_management_system
    src/main.cpp
    src/Student.cpp
    src/Validator.cpp
    src/FileManager.cpp
)

target_include_directories(student_management_system PRIVATE include)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(student_management_system PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
    target_compile_options(student_management_system PRIVATE /W4)
endif()
