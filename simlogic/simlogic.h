/*
====== Legal notices

Copyright 2017 Jacques de Hooge, GEATEC engineering, www.geatec.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
Understanding this header requires understanding some C++
But using it merely requires C knowledge
*/

#include "simulation.h"

#ifdef __arduino__
#include <Arduino.h>  // Will provide all Arduino stuff
#ifdef __debug__
#include <stdlib.h>   // Will provide itoa
#endif
#endif

struct CircuitElement {
    bool value;
    const char * const name;
    CircuitElement *next;
    
    CircuitElement (const char * const name);    
    virtual void evaluate () = 0;       
};

struct False: CircuitElement {
    False (const char * const name);
    void evaluate ();
};

struct True: CircuitElement {
    True (const char * const name);
    void evaluate ();
};

struct Input: CircuitElement {
    CircuitElement *in;
    
    Input (const char * const name);
    void evaluate ();
};

struct And: CircuitElement {
    CircuitElement *inA, *inB;
    
    And (const char * const name);
    void evaluate ();
};

struct Or: CircuitElement  {
    CircuitElement *inA, *inB;    
    Or (const char * const name);
    void evaluate ();
};

struct Xor: CircuitElement  {
    CircuitElement *inA, *inB;    
    
    Xor (const char * const name);
    void evaluate ();
};

struct Not: CircuitElement  {
    CircuitElement *in;
    
    Not (const char * const name);
    void evaluate ();
};

struct Oneshot: CircuitElement  {
    CircuitElement *in;
    bool oldInputValue;
    
    Oneshot (const char * const name);
    void evaluate (); 
};

struct Latch: CircuitElement  {
    CircuitElement *set, *reset;
    
    Latch (const char * const name);
    void evaluate ();
};

struct CircuitEvaluator {
    CircuitElement *first, **lastSlot;
#ifdef __debug__
    int cycleNr;
#endif
    
    CircuitEvaluator ();
    void add (CircuitElement &element);
    void evaluate ();
};

extern CircuitEvaluator evaluator;

#define create(type, name) type name (#name); evaluator.add (name)
extern void connect (CircuitElement &source, CircuitElement *&sinkInput);
extern void evaluate ();

#ifdef __debug__
#ifdef __arduino__
struct SerialStream {
    SerialStream &operator<< (const char * const data);
    SerialStream &operator<< (bool data);
    SerialStream &operator<< (int data);
    SerialStream &operator>> (char * const data);
};

extern const char * const endl;
#else
#include <iostream>
using namespace std;
#endif
#endif

