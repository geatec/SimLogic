What is SimLogic
================

SimLogic is a simple logic simulator for educational purposes. It can work in conjunction with an Arduino single board embedded computer. First *create* circuit elements and then *connect* them, as in the following code for a half-adder: ::

    #include "simlogic.h"

    int main () {    
        create (Input, inputA);
        create (Input, inputB);
        create (And, anAnd);
        create (Not, aNot);

        connect (inputA, anAnd.inA);
        connect (inputB, anAnd.inB);
        connect (anAnd, aNot.in);

        while (true) {
            evaluate ();
        }
        
        return 0;
    }

Features
========

Each SimLogic program is defined in a file called *simulation.cpp*. Note that this one file is the only "valuable" user made file in a project. All the rest is boilerplate code, identical for each project. A simulation can run in three ways, depending on macro defintions in *simulation.h*, namely:

1. Console I/O on a PC using a command prompt: *console* defined in *simulation.h*, compilation with *compile.bat* on PC
2. Console I/O on an Arduino using its IDE's serial monitor: *console* defined, compilation in Arduino IDE. In this case hardware outputs, e.g. LED's will also work. On the serial monitor, set *Autocroll* on, set the line terminator to *Newline* and set the speed to *9600 baud*. Input happens in one-line entry field at the top of the serial monitor window and is echoed together with output to the multinline text view field at the bottom.
3. Hardware I/O on an Arduino, using e.g. buttos and LED's): *console* not defined, compilation in Arduino IDE.

Input format utilizing console I/O
==================================

- Example 1 t/m 4: Enter INPUT values as 0 or 1
- Example 5: Enter INPUT values as 00, 01, 10 or 01

Hardware
========

Example *ex4_full_adder* was instrumented for the Arduino, by adding pin assignments and I/O statements.

It was tested on an Arduino due, with the following test circuit:

.. figure:: http://www.qquick.org/simlogic/full_adder.jpg
	:alt: Screenshot of hardware for the full adder example.
	
	**Hardware for the full adder**

Note that for educational purposes, the LED's can best be placed into a circuit diagram of the logic that is simulated.

Remarks
=======

- All examples have been precompiled for Windows with g++ using the *compile.bat* scripts in the individual example folders and will use console I/O.
- Due to their simplicity the examples should also compile on Linux and OS X, using appropriate C++ compilers and shell scripts or make files.
- When running in a console Window, terminate each program simply by CTRL + C.
- There's no error protection, so after an erroneous input best restart the program.
- While *simlogic.h* and *simlogic.cpp* use C++ idiom, the examples only use C'ish idiom.
- Only *simulation.cpp* of *ex4_full_adder* has been instrumented with Arduino facilities, so is ready to run on an Arduino. Instrumenting boils down to adding a few conditionally compiled lines, as can be seen in this example.
- The other examples can be adapted likewise, if running on an Arduino is required.
- To run on an Arduino, go to the example directory, edit *simulation.h* according to wether or not console I/O is desired, and then use [Sketch][Upload].
- The file *build.py* copies the files that all examples have in common to the example directories, renaming *rename.ino* to match the directory that holds it, as required by the Arduino IDE.
- In general the "everything in one directory" approach of the Arduino IDE is followed, to keep things simple.
- To edit the common files, use the ones in the parent directory and then run *build.py*, preferably using Python 3.6, although it may very well run with almost any Python version.
- When running *build.py* all examples will be compiled for PC as well.

Other packages you might like
=============================

- Interactive PLC simulator with Arduino code generation: https://pypi.python.org/pypi/SimPyLC
- Lean and mean Python to JavaScript transpiler featuring multiple inheritance https://pypi.python.org/pypi/Transcrypt
- Numscrypt (under construction, very early stage), experimental port of a microscopic part of NumPy to Transcrypt, using JavaScript typed arrays: https://pypi.python.org/pypi/Numscrypt
- Multi-module Python source code obfuscator: https://pypi.python.org/pypi/Opy
- A lightweight Python course taking beginners seriously (under construction): https://pypi.python.org/pypi/LightOn
- Event driven evaluation nodes: https://pypi.python.org/pypi/Eden
