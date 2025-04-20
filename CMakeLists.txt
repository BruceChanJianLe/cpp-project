cmake_minimum_required(VERSION 3.22)
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
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -fPIC -Wshadow")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-Wnon-virtual-dtor>")
endif()


include(FetchContent)
# Avoid warnings in CMake 3.24.0:
if (CMAKE_VERSION VERSION_GREATER "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

# Add Kokkos
FetchContent_Declare(
  Kokkos
  URL      https://github.com/kokkos/kokkos/releases/download/4.5.01/kokkos-4.5.01.tar.gz
  URL_HASH SHA256=52d003ffbbe05f30c89966e4009c017efb1662b02b2b73190670d3418719564c
)
FetchContent_MakeAvailable(Kokkos)

# Add mdspan
FetchContent_Declare(
  mdspan
  GIT_REPOSITORY https://github.com/kokkos/mdspan.git
  GIT_TAG        mdspan-0.6.0
)
FetchContent_MakeAvailable(mdspan)

# Common libraries
find_package(TBB REQUIRED)

# hello world example (logic gate OR)
add_executable(logic_gate_or ./src/logic_gate_or.cpp ./src/mlp.cpp)
target_include_directories(logic_gate_or PUBLIC include)
target_link_libraries(logic_gate_or PRIVATE TBB::tbb std::mdspan Kokkos::kokkos)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(logic_gate_or PUBLIC -stdlib=libc++ -fexperimental-library)
  target_link_options(logic_gate_or PUBLIC -stdlib=libc++ -fexperimental-library)
endif()

# logic gate xor
add_executable(logic_gate_xor ./src/logic_gate_xor.cpp ./src/mlp.cpp)
target_include_directories(logic_gate_xor PUBLIC include)
target_link_libraries(logic_gate_xor PRIVATE TBB::tbb std::mdspan Kokkos::kokkos)
