cmake_minimum_required(VERSION 3.12)

project("lab5" CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} "lab5.cpp" "Class.cpp" "Class.h"  "Func.cpp" "Func.h" "Menu.cpp")

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "GAppleClang" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "NU")
  target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Weffc++" "-Wextra" "-Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  endif()
  target_compile_options(${PROJECT_NAME} PRIVATE "/W4" "/utf-8")
endif()
