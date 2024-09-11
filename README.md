# today

Use **today** to review what you've done today! - In the future. Today is under construction now.

![Static Badge](https://img.shields.io/badge/C%2B%2B-17-blue) ![GitHub License](https://img.shields.io/github/license/Adamska1008/today)

## Usage

### Counting everyday commit

By default **today** shows your commit today. Without specified `--author` every commit is counted.

```bash
Use today to review what you've accomplished today!
Usage:
  today [OPTION...]

  -d, --directory arg  The working directory to be check (default: .)
  -h, --help           Print usage
```

## Setup

### Build from source

**today** depends on `libgit2`, so make sure you've already installed ligbit2 >= 1.0. On ubuntu, run:

```bash
sudo apt-get update
sudo apt-get install libgit2-dev
```

Ensure that you meet:

+ CMake Version > 3.22
+ C++ Compiler with C++17 support

Run first:

```bash
git submodule init
git submodule update
```

In project source directory run command:

```bash
cmake -S . -B build
cmake --build build
```

Then you get binary in `build/src/today`.

### Install

```bash
cmake --install build --component binary # generally requires sudo 
````
