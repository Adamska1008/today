# today

![Static Badge](https://img.shields.io/badge/C%2B%2B-17-blue) ![GitHub License](https://img.shields.io/github/license/Adamska1008/today)

Today is a lightweight tool for tracking daily code commits, allowing developers to easily review the number of commits, lines changed and files modified each day.

## Usage

### Counting everyday commit

By default **today** shows your commit today. Without specified `--author` every commit is counted.

```bash
Use today to review what you've accomplished today!
Usage:
  today [OPTION...]

  -o, --offset arg     Offset from today (default: 0)
  -d, --directory arg  The working directory to be check (default: .)
  -h, --help           Print usage
```

```bash
# run
today
```

```sh
# output is like
Total: Commits 5, Lines Added 118, Lines Removed 9, Files Changed 6.
+=========+======================================+======================+=============+===============+===============+
| Author  | Message                              | Time                 | Lines Added | Lines Removed | Files Changed |
+=========+======================================+======================+=============+===============+===============+
| adamska | doc: polish doc libgit2pp_implement  | 2024-09-11 23:37 CST | 3           | 5             | 1             |
+=========+======================================+======================+=============+===============+===============+
| adamska | feat: use zoned_time                 | 2024-09-11 23:30 CST | 9           | 3             | 4             |
+=========+======================================+======================+=============+===============+===============+
| adamska | feat: support cmake --install        | 2024-09-11 17:07 CST | 15          | 4             | 3             |
+=========+======================================+======================+=============+===============+===============+
| adamska | feat: add --help option              | 2024-09-11 12:43 CST | 75          | 46            | 3             |
+=========+======================================+======================+=============+===============+===============+
| adamska | deps: add cxxopts                    | 2024-09-11 11:42 CST | 16          | 9             | 6             |
+=========+======================================+======================+=============+===============+===============+
```

Use `offset` options to check your commit yesterday or before yesterday.

```sh
today --offset=-1 # generally only negative number works, you can't predict the future
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
