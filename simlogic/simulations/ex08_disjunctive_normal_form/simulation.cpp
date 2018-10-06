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

/*
V (3, 5, 6) (p A q A r)

#   p   q   r   phi
0   0   0   0   0
1   0   0   1   0
2   0   1   0   0
3   0   1   1   1
4   1   0   0   0
5   1   0   1   1
6   1   1   0   1
7   1   1   1   0

(~p A q A r) V (p A ~q A r) V (p A q A ~r)
*/

int main () {  
    /*
    Build logical circuit representing conjunctive normal form of truth table above
    Connect LED's to all circuits and verify against truth table
    */
    
    // p, q and r
    
    create (Input, p);
    create (Input, q);
    create (Input, r);
    
    // not p, not q and not r
    
    create (Not, notP);
    connect (p, notP.in);
    
    create (Not, notQ);
    connect (q, notQ.in);
    
    create (Not, notR);
    connect (r, notR.in);
    
    // 1st term
    
    create (And, factor1);
    connect (notP, factor1.inA);
    connect (q, factor1.inB);
    
    create (And, term1);
    connect (factor1, term1.inA);
    connect (r, term1.inB );

    // 2nd term
    
    create (And, factor2);
    connect (p, factor2.inA);
    connect (notQ, factor2.inB);
    
    create (And, term2);
    connect (factor2, term2.inA);
    connect (r, term2.inB);

    // 3rd term
    
    create (And, factor3);
    connect (p, factor3.inA);
    connect (q, factor3.inB);
    
    create (And, term3);
    connect (factor3, term3.inA);
    connect (notR, term3.inB);
    
    // Combine terms into disjunction phi
    
    create (Or, term12);
    connect (term1, term12.inA);
    connect (term2, term12.inB);
    
    create (Or, phi);
    connect (term12, phi.inA);
    connect (term3, phi.inB);
    
    while (true) {
        evaluate ();
    }
    
    return 0;
}
