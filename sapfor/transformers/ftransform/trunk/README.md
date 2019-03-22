# Info
Fortran Transform application.

### How to build examples
1. cd to root directory (ftransform/trunk/)
2. `cd ./examples/combine` only _combine_ works as of now
3. `../rebuild.sh` parser and ftransform should build themselves.

### How to build ftransform
1. cd to root directory (ftransform/trunk/)
2. `./rebuild.sh`
6. add `ftransform` to antivirus exceptions if necessary
ftransform is the resulting application.

### How to build parser
1. cd to root directory (ftransform/trunk/)
2. `cd ./parser`
2. `./rebuild.sh`
6. add `parser` to antivirus exceptions if necessary
parser is the resulting application.

N.B.: Working with source fortran files requires a parser.

## About `paths.default.txt`
`paths.default.txt` contains paths from current folder to various Sage folders.
Default file expects structure of:
```
/common_parent_dir
  /dvm
    /fdvm
      /trunk
        /include
        /parser
        /Sage
          /h
          /lib
            /include
  /sapfor
    /transformers
      /ftransform
        /trunk
```

`paths.txt` can override `paths.default.txt`. `paths.txt` should have same keys and appropriate values.
`paths.txt` should not be uploaded to SVN.

# Usage
Using `program.f90` as source code filename. (just an example, other names are ok)
1) Create `program.f90` - Fortran program (with `!PRG` comments)
    - `*.f90` extension is important and must be `*.f90`.
2) Then parse `parser -lgstd program.f90` (see parser README for details)
    - Output is `program.dep` parse result and sage++ project file `dvm.proj` (if there are errors in source `*.f90` they will appear here)
3) launch ftransform `ftransform` from the same folder as `dvm.proj`. 
    - Project file name can be overridden by passing an argument. `ftransform myProjName.proj`
4) Output is `trans.f90` - transformed code and `simple.log` - debug info about transformation process.
    - Previous log files are renamed into timestamped file

Check /ftransform/trunk/examples/combine for a simple example. 