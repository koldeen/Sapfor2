# Compilation and build of parser:
1. cd to this directory. {svn root}/parser
3. `mkdir build`
4. `cd build`
5. `cmake ..`
6. `cmake --build .`

It may be required to add parser.exe to antivirus exceptions.
parser.exe is the resulting application.

#Usage
- Input: fortran source file with `*.f90` extension
- Launch with `parser -lgstd [fortran source file]` 
  - on Unix add dot `./parser -lgstd [fortran source file]`
- Output: `dvm.proj` and `*.dep` file with same name as fortran source file


