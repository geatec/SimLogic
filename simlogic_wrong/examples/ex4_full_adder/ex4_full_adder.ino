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
#undef main

#include "simlogic.h"

int main  () {
    //  BEGIN Arduino initialisation
#ifndef debug
    init ();
#ifdef USBCON
    USBDevice.attach ();
#endif
#endif
    // END Arduino initialisation
    
    create (Input, inputA);
    create (Input, inputB);
    create (Input, inputCarry);
    
    create (Xor, xorAB);
    create (And, anAnd);
    create (And, andAB);
    
    create (Xor, sum);
    create (Or, carry);

    connect (inputA, xorAB.inA);
    connect (inputB, xorAB.inB);
    connect (inputA, andAB.inA);
    connect (inputB, andAB.inB);
    
    connect (xorAB, sum.inA);
    connect (inputCarry, sum.inB);
    
    connect (xorAB, anAnd.inA);
    connect (inputCarry, anAnd.inB);
    
    connect (anAnd, carry.inA);
    connect (andAB, carry.inB);
    
    // BEGIN Arduino pin config
//#ifndef debug
    pinMode (2, INPUT); pinMode (3, INPUT); pinMode (4, INPUT);
    pinMode (5, OUTPUT); pinMode (6, OUTPUT); pinMode (7, OUTPUT); pinMode (8, OUTPUT); pinMode (9, OUTPUT);
//#endif;
    // END Arduino pin config

    Serial.begin (9600);
    
    for (;;) {  // Endless main program loop
        // BEGIN Arduino reads
//#ifndef debug
        inputA.value = digitalRead (2);
        inputB.value = digitalRead (3);
        inputCarry.value = digitalRead (4);
//#endif        
        // END Arduino reads
        evaluate ();
        Serial.write (digitalRead (2) ? "true" : "false");
        Serial.println ();
        
        // BEGIN Arduino writes
//#ifndef debug
        digitalWrite (5, xorAB.value);
        digitalWrite (6, anAnd.value);
        digitalWrite (7, andAB.value);
        digitalWrite (8, sum.value);
        digitalWrite (9, carry.value);
//#endif        
        // END Arduino writes
        
        // BEGIN Arduino serial com
//#ifndef debug
        if (serialEventRun) {
            serialEventRun();
        }
//#endif
        // END Arduino serial com
    }
    
    return 0;
}
