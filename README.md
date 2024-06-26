# Advent of Init
A C++ CLI tool that lets you initialize Advent of Code Puzzles. This works by providing a "logged in" session cookie to the tool, which then fetches the input data from adventofcode.com, initializes a folder structure and puts it alongside an optional template provided by the user.   
This Project also provides a default template including a tested aocutils.h which provides common functionality for Advent of Code Puzzles. Feel free to ignore this and replace it with your own template or don't use it at all.

# Usage
## Required
You need to download your adventofcode.com session cookie from a session where you are logged in and either paste it into a file or pass it to AdventOfInit using the --cookie parameter
## Optional
- Specify the day (defaults to current day if smaller than 25 or 1):  
`--day <int>` -> puzzle day  
- Specify the year (defaults to current year if already december or last year):  
`--year <int>` -> event year    
- Specify the path (defaults to <year>/Day<day> with <day> being 2 digits).  
`--path <string>` -> filepath  
- Specify the template to use (defaults to none)  
The template is a folder which contains files which you want alongside your input.txt. In this example its a very simple CMake project that contains a C++ header only utils library
You can template filenames by using @YEAR@ and @DAY@ which AdventOfInit will replace with the year and day respectively  
`--template <string>` -> folder path to the template you want to use  
- Specify the Session Cookie:  
`--cookie <string>` -> cookie or filename containing the cookie (defaults to ./session.txt)  

# How to Build
## Build requirements
- CMake
- Conan
- A C++ compiler

## Build steps
Depends on Conan Package manager  
```
$ conan install . --output_folder=build --build=missing
$ cd build
$ cmake .. -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"
$ cmake --build . --config Release
```
  
Building openssl using conan on windows (a cpr/libcurl dependency) can be a bit tricky, but it worked for me with Visual Studio Code 17 2022.
Couldn't get it to build on windows with clang / gcc, but it worked on linux.

# Releases
Windows: https://github.com/JuliusPallesen/AdventOfInit/releases/tag/v1.0
