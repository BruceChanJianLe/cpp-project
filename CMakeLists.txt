cmake_minimum_required (VERSION 3.22)
project(cpp-project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Using clang
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

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
find_package(TBB REQUIRED)

# hello world example (logic gate OR)
add_executable(logic_gate_or ./src/logic_gate_or.cpp ./src/mlp.cpp)
target_include_directories(logic_gate_or PUBLIC include)
target_link_libraries(logic_gate_or TBB::tbb)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(logic_gate_or PUBLIC -stdlib=libc++ -fexperimental-library)
  target_link_options(logic_gate_or PUBLIC -stdlib=libc++ -fexperimental-library)
endif()
