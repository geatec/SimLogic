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

int main  () {
    create (Input, set);
    create (Input, reset);
    create (Latch, latch);
    create (Oneshot, oneshot);

    connect (set, latch.set);
    connect (reset, latch.reset);
    connect (latch, oneshot.in);

    while (true) {
        evaluate ();
    }
    
    return 0;
}
