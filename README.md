## Introduction

Writing a fully connected neural network in C++.
Currently, this project is only tested on Arch Linux.

## Dependencies

```bash
sudo pacman -S clang libc++
```

## Building

Build using the `cmake` command.  
```bash
export CC=clang
export CXX=clang++
cmake -S . -B build
cmake --build build
```

## Running

Run the respective executable in the `build` directory.  
```bash
./build/logic_gate_or
```
