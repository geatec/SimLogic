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

#include <simlogic.h>

int main  () {
    //  BEGIN Arduino initialisation
#ifndef debug
    init ();
#ifdef USBCON
    USBDevice.attach ()
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
#ifndef debug
    pinMode (0, INPUT); pinMode (1, INPUT); pinMode (1, INPUT);
    pinMode (4, OUTPUT); pinMode (5, OUTPUT); pinMode (6, OUTPUT); pinMode (7, OUTPUT);
#endif
    // END Arduino pin config
    
    for (;;) {  // Endless main program loop
        // BEGIN Arduino reads
#ifndef debug
        inputA.value = digitalRead (0);
        inputB.value = digitalRead (1);
        inputCarry.value = digitalRead (2);
#endif        
        // END Arduino reads
        evaluate ();
        
        // BEGIN Arduino writes
#ifndef debug
        digitalWrite (xorAB.value, 3);
        digitalWrite (anAnd.value, 4);
        digitalWrite (andAB.value, 5);
        digitalWrite (sum.value, 6);
        digitalWrite (carry.value, 7);
#endif        
        // END Arduino writes
        
        // BEGIN Arduino serial com
#ifndef debug
        if (serialEventRun) {
            serialEventRun();
        }
#endif
        // END Arduino serial com
    }
    
    return 0;
}
