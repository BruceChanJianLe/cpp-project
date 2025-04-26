## Introduction

This is based on the talk "Using Modern C++ to Eliminate Virtual Functions"
by Jonathan Gopel at CppCon 2022. Definitely checkout the talk if you have time.

## Task

1. We want to monitor some set of devices on the same network that we are on
1. Each device type is unique in how we must interact with it
1. It is not possible to know the device's connection information before we
   join the network - we must find it in situ

## Usage

1. Clone repo shallowly. You won't need the other branches!
```bash
git clone --depth 1 -b eliminate_virtual https://github.com/BruceChanJianLe/cpp-project.git
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
./build/device_virtual
./build/device_concept
```
