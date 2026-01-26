## Introduction

This leak detector is an example shown in the book "C++ Memomry Management" in
chapter 8, it's a great book, do check it out! [link](https://www.packtpub.com/en-sg/product/c-memory-management-9781805128243)


## Usage

1. Clone repo shallowly. You won't need the other branches!
```bash
git clone --depth 1 https://github.com/BruceChanJianLe/cpp-project.git -b leak_detector
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
./build/almost_correct_leak_detector
```
