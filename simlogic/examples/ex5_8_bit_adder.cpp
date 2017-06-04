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

#define createBit(i)                        \
    create (Input, input0##i);              \
    create (Input, input1##i);              \
    create (Input, inputCarry##i;           \
                                            \
    create (Xor, xorAB##i);                 \
    create (And, anAnd##i);                 \
    create (And, andAB##i);                 \
                                            \
    create (Xor, sum##i);                   \
    create (Or, carry##i);                  \
                                            \
    connect (inputA##i, xorAB##i.inA);      \
    connect (inputB##i, xorAB##i.inB);      \
    connect (inputA##i, andAB##i.inA);      \
    connect (inputB##i, andAB##i.inB);      \
                                            \
    connect (xorAB##i, sum##i.inA);         \
    connect (inputCarry##i, sum##i.inB);    \
                                            \
    connect (xorAB##i, anAnd##i.inA);       \
    connect (inputCarry##i, anAnd##i.inB);  \
                                            \
    connect (anAnd##i, carry##i.inA);       \
    connect (andAB##i, carry##i.inB)

int main  () {
    
    createBit (0);
    createBit (1);
    createBit (2);
    createBit (3);
    createBit (4);
    createBit (5);
    createBit (6);
    createBit (7);
    
    connect (carry0, inputCarry1)
    connect (carry1, inputCarry2)
    connect (carry2, inputCarry3)
    connect (carry3, inputCarry4)
    connect (carry4, inputCarry5)
    connect (carry5, inputCarry6)
    connect (carry6, inputCarry7)

    for (;;) {  // Forever loop, idiomatic since K&R C
        // All Arduino digitalRead's go here
        
        // Evaluate interconnected circuit once
        evaluate ();
        
        // All Arduino digitalWrite's go here
    }
    
    return 0;
}
