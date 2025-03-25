cmake_minimum_required (VERSION 3.22)
project(cpp-project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
  # "Debug", "Release", "MinSizeRel", "RelWithDebInfo"
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -Wdeprecated -fPIC -Wshadow")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-Wnon-virtual-dtor>")
endif()

# Common libraries
find_package(fmt REQUIRED)
find_package(TBB REQUIRED)

# hello world example
add_executable(hello_world ./src/hello_world.cpp)
target_include_directories(hello_world PUBLIC include)
target_link_libraries(hello_world fmt::fmt TBB::tbb)
