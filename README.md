## Introduction

This repository is a template or a starting point that is:
- A CMake Project
- Well structured project with examples
- With standard compile flags

Need not worry about setting everything from scratch.

## Usage

1. Clone repo shallowly. You won't need the other branches!
```bash
git clone --depth 1 https://github.com/BruceChanJianLe/cpp-project.git
```
1. Populate `src` and `include` directory with your testing code.

## Building

Build using the `cmake` command.  
```bash
cmake -S . -B build
cmake --build build
```

## Running

Run the respective executable in the `build` directory.  
```bash
./build/hello_world
```
