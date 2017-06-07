**Features**

Each SimLogic program is defined in a file called *simulation.cpp*. Note that this one file is the only "valuable" user made file in a project. All the rest is boilerplate code, identical for each project. A simulation can run in three ways, depending on macro defintions in *simulation.h*, namely:

1 Console I/O on a PC (Command prompt), *__debug__* defined, *__arduino__* not defined.
2 Console I/O on an Arduino (Serial monitor, but LED's function as well), *__debug__* defined, *__arduino__* defined.
3 Hardware I/O on an Arduino (LED's and buttons), *__debug__* not defined, *__arduino__* not defined.

To run the examples on an Arduino, rather than a PC, define symbol *__arduino__*.

To debug using console I/O rather than switches, define symbol *__debug__*. On an Arduino, debugging happens using serial I/O and the serial monitor on the Arduino IDE.
To use it, set *Autocroll* on, set the line terminator to *Newline* and set the speed to *9600 baud*. Input happens in one-line entry field at the top and is echoed together with output to the text view field below.

On a PC a regular command prompt window is used for input and output.

**Each simulation example has a *compile.bat*

**Usage**

- Example 1 t/m 4: Enter INPUT values as 0 or 1
- Example 5: Enter INPUT values as 00, 01, 10 or 01

**Hardware**

Example *ex4_full_adder* was instrumented for the Arduino, by adding pin assignments, I/O statements and an optional *__main__*, which will be called in the *setup* function in the *.ino* file. For variable scoping reasons, *__main__* has its own program loop, so the *loop* function in the *.ino* file will not be used.

It was tested on an Arduino due, with the following test circuit:

.. figure:: http://www.qquick.org/simlogic/full_adder.jpg
	:alt: Screenshot of hardware for the full adder example.
	
	**Hardware for the full adder**

Note that for educational purposes, the LED's can best be placed into a circuit diagram of the logic that is simulated.

**Remarks**

- All examples have been precompiled for Windows with g++ using compile_all.bat and will use console I/O.
- Due to their simplicity the examples should also compile on Linux and OS X,
using appropriate C++ compilers and shell scripts or make files.
- When running in a console Window, terminate each program simply by CTRL + C.
- There's no error protection, so after an erroneous input best restart the program.
- While simlogic.h and simlogic.cpp use C++ idiom, the examples only use C'ish idiom.
- Only *simulation.cpp* of *ex4_full_adder* has been instrumented with Arduino facilities (So is ready to run on an Arduino). Instrumenting boils down to adding a few conditionally compiled lines, as can be seen in this example.
- The other examples can be adapted likewise, if running on an Arduino is required.
- To run on an Arduino, go to the example directory, edit *simulation.h* to adapt the macro definitions en then use [Sketch][Upload].
- There file *build.py* copies the files that all examples have in common to the example directories, renaming *rename.ino* to match the directory that holds it, as required by the Arduino IDE.
- In general the "everything in one directory" approach of the Arduino IDE is followed, to keep things simple.
- To edit the common files, use the ones in the parent directory and then run *build.py*, preferably using Python 3.6, although it may very well run with almost any Python version.


