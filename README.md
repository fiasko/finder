# grep like finder tool
This application is file content search tool similar to grep. Basic functionality is to search string from file or files. Both basic string search and regular expression search patterns are supported. The application searches each file in parallel thread to speed things up when large directories are searched.

# Dependencies
- C++20 compiler toolchain (Visual Studio 2022)
- cmake
- gtest unit test framework

# Build
``` shell
cd finder
cmake
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
