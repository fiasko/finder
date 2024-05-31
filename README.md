# grep like finder tool
This tool was developed in one week from sratch. AI tools were not used intentionally other than getting initial instructions how to setup new CMake project.
This application is file content search tool similar to grep. Basic functionality is to search string from file or files. Both basic string search and regular expression search patterns are supported. The application searches each file in parallel thread to speed things up when large directories are searched.

# Dependencies
- C++20 compiler toolchain (Visual Studio 2022)
- cmake
- gtest unit test framework

# Build
``` shell
cd finder
mkdir build
cd build
cmake ..
cmake --build .
```
  
# usage
``` shell
finder [OPTION]... PATTERN [FILE]
  -G    PATTERN is basic regular expressions
  -r    recursive search
```

example:
``` shell
finder "text" "myfile.txt"
```

``` shell
finder "text" "myfi*.txt"
```

``` shell
finder -r -G "^begin.*" "folder/"
```

# Testig
To run tests use ctest. You can also run native google test by running test_finder.exe in a directry with the testdata directory (eg. test or build directory).
