# today

Use **today** to review what you've done today! - In the future. Today is under construction now.

![Static Badge](https://img.shields.io/badge/C%2B%2B-17-blue) ![GitHub License](https://img.shields.io/github/license/Adamska1008/today)

## Setup

### Build from source

**today** depends on `libgit2`, so make sure you've already installed ligbit2 >= 1.0. On ubuntu, run command:

```bash
sudo apt-get update
sudo apt-get install libgit2-dev
```

Ensure that you meet:

+ CMake Version > 3.22
+ C++ Compiler with C++17 support

Navigate to project source directory and run command:

```bash
cmake -S . -B build
cmake --build build
```
