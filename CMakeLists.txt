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

# Device virtual
add_executable(device_virtual
  ./src/device_virtual.cpp
  ./src/virtual/devices.cpp
  ./src/virtual/switch.cpp
  ./src/virtual/dimmer.cpp
  ./src/virtual/device_manager.cpp
)
target_include_directories(device_virtual PUBLIC include)
target_link_libraries(device_virtual fmt::fmt TBB::tbb)
