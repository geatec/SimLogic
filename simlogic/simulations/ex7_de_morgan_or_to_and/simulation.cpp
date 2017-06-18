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
    Visually check equivalence between notRainyOrNotCold and not_rainyAndCold
    */
    
    // It isn't rainy or it isn't cold
    
    create (Not, notRainy);
    connect (rainy, notRainy.in);

    create (Not, notCold);
    connect (cold, notCold.in);
    
    create (Or, notRainyOrNotCold);
    connect (notRainy, notRainyOrNotCold.inA);
    connect (notCold, notRainyOrNotCold.inB);
    
    // It isn't rainy and cold
    
    create (And, rainyAndCold);
    connect (rainy, rainyAndCold.inA);
    connect (cold, rainyAndCold.inB);
    
    create (Not, not_rainyAndCold);
    connect (rainyAndCold, not_rainyAndCold.in);
    
    while (true) {
        evaluate ();
    }
    
    return 0;
}
