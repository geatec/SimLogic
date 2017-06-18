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
A (1, 2) (~p V ~q V ~r)

#	p	q	r	phi	
0	0	0	0	1
1	0	0	1	0
2	0	1	0	0
3	0	1	1	1
4	1	0	0	1
5	1	0	1	1
6	1	1	0	1
7	1	1	1	1

~ [(~p A ~q A r) V (~p A q A ~r)] =
~ (~p A ~q A r) A ~ (~p A q A ~r) =
(p V q V ~r) A (p V ~q V r)
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
    
    // not q and not r

    create (Not, notQ);
    connect (q, notQ.in);
    
    create (Not, notR);
    connect (r, notR.in);
    
    // 1st factor
    
    create (Or, term1);
    connect (p, term1.inA);
    connect (q, term1.inB);
    
    create (Or, factor1);
    connect (term1, factor1.inA);
    connect (notR, factor1.inB);

    // 2nd factor

    create (Or, term2);
    connect (p, term2.inA);
    connect (notQ, term2.inB);
    
    create (Or, factor2);
    connect (term2, factor2.inA);
    connect (r, factor2.inB);
    
    // Combine factors into conjunction phi
    
    create (And, phi);
    connect (factor1, phi.inA);
    connect (factor2, phi.inB);
    
    while (true) {
        evaluate ();
    }
    
    return 0;
}
