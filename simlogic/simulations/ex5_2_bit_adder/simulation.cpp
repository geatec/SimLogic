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
00 + 00 = 000
00 + 01 = 001
00 + 10 = 010
00 + 11 = 011

01 + 00 = 001
01 + 01 = 010
01 + 10 = 011
01 + 11 = 100

10 + 00 = 010
10 + 01 = 011
10 + 10 = 100
10 + 11 = 101

11 + 00 = 011
11 + 01 = 100
11 + 10 = 101
11 + 11 = 110
*/

#include "simlogic.h"

/*
Define macro for easy expansion to n bits
Stay within C idiom
*/

#define createBit(i)                        \
    create (Input, inputA##i);              \
    create (Input, inputB##i);              \
    create (Input, inputCarry##i);          \
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

#define getBit(nrString, index) nrString [1 - index] == '1' ? (CircuitElement *) &aTrue : (CircuitElement *) &aFalse
    
int main  () {
    create (False, aFalse);
    create (True, aTrue);
    
    createBit (0);
    createBit (1);
    
    connect (aFalse, inputCarry0.in);
    connect (carry0, inputCarry1.in);
    
    while (true) {
#ifdef console
        char nr1 [3];
        cout << "First number: ";
        cin >> nr1;
        char nr2 [3];
        cout << "Second number: ";
        cin >> nr2;
        cout << endl;
        
        inputA0.in = getBit (nr1, 0);
        inputA1.in = getBit (nr1, 1); 
        
        inputB0.in = getBit (nr2, 0);
        inputB1.in = getBit (nr2, 1);
#endif
        evaluate ();
#ifdef console
        cout << inputA1.value << inputA0.value;
        cout << " + ";
        cout << inputB1.value << inputB0.value;
        cout << " = ";
        cout << carry1.value << sum1.value << sum0.value << endl;
        cout << endl;
#endif
    }
    
    return 0;
}
