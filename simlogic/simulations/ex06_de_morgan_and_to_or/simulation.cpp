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

#include "simlogic.h"

int main () {    
    create (Input, rainy);
    create (Input, cold);
    
    /*
    Connect LED's to every created circuit
    Visually check equivalence between notRainyAndNotCold and not_rainyOrCold
    */
    
    // It isn't rainy and it isn't cold
    
    create (Not, notRainy);
    connect (rainy, notRainy.in);

    create (Not, notCold);
    connect (cold, notCold.in);
    
    create (And, notRainyAndNotCold);
    connect (notRainy, notRainyAndNotCold.inA);
    connect (notCold, notRainyAndNotCold.inB);
    
    // It isn't rainy or cold
    
    create (Or, rainyOrCold);
    connect (rainy, rainyOrCold.inA);
    connect (cold, rainyOrCold.inB);
    
    create (Not, not_rainyOrCold);
    connect (rainyOrCold, not_rainyOrCold.in);
    
    while (true) {
        evaluate ();
    }
    
    return 0;
}
