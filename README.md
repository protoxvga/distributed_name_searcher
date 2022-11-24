# Distributed Text Searcher
Program to search a word in multiple txt files thanks to Open MPI distribution.
Program developed for an assignment during my fourth year in the Griffith College (Dublin)

## Installation

This program needs Open MPI to work.
Open MPI is a library for distributed system in C++.

Try to follow this steps to install open MPI on your system :
- **Windows**:  Sorry, cannot help you on this one :(
- **Mac OS**:   [Instructions](https://stackoverflow.com/questions/42703861/how-to-use-mpi-on-mac-os-x)
- **Linux**:    [Instructions](https://edu.itp.phys.ethz.ch/hs12/programming_techniques/openmpi.pdf)

## Usage

You can find on the zip file 4 text files used in the program.
Modify on the program text files name if you want to add nodes or different text files.

### Compilation
```mpic++ name_searcher.cpp -o <executable-name>```

### Execution

```mpiexec -n 4 <executable-name> <text-to-search>```

example: ```mpiexec -n 4 ./a.out is```
