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

    for (;;) {  // Forever loop, idiomatic since K&R C
        // All Arduino digitalRead's go here
        
        // Evaluate interconnected circuit once
        evaluate ();
        
        // All Arduino digitalWrite's go here
    }
    
    return 0;
}
