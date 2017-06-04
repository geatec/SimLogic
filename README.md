Usage:

- Example 1 t/m 4: Enter INPUT values as 0 or 1
- Example 5: Enter INPUT values as 00, 01, 10 or 01

Remarks:

- The examples have been precompiled for Windows with g++ using debug_all.bat,
but due to their simplicity they should also compile on Linux and OS X,
using appropriate C++ compilers and shell scripts or make files.
- To use console input and output, use the compilation batches with the word 'debug' in it.
- To use a single board computer with buttons and LED's, use the compilation batches with the word 'compile' in it.
- Single board usage has not yet been tested, but the required modifications should be trivial.
- Terminate each program simply by CTRL + C.
- There's no error protection, so after an erroneous input best restart the program.
- While simlogic.h and simlogic.cpp use C++ idiom, the examples only use C'ish idiom.
