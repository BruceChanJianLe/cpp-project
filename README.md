## Introduction

A compile time fibonacci generator.

## Usage

1. Clone repo shallowly. You won't need the other branches!
```bash
git clone --depth 1 https://github.com/BruceChanJianLe/cpp-project.git -b compile_time_fibonacci
```

## Building

Build using the `cmake` command.  
```bash
cmake -S . -B build
cmake --build build
```

## Running

Run the respective executable in the `build` directory.  
```bash
# std::size_t version
./build/fibonacci_example
# int version
./build/fibonacci_example_int
```
