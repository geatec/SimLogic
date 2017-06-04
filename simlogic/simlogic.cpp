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

#ifdef debug   // Don't generate any IO code for a single board computer
#include <iostream>
using namespace std;
#endif

CircuitElement::CircuitElement (const char *name): name (name), value (0), next (0) {
}

Input::Input (const char *name): CircuitElement (name) {
}
    
void Input::evaluate () {
#ifdef debug
    char answer [2];
    cout << "INPUT " << name << ": " << value << " ";
    cin.getline (answer, 2);
    if (answer [0] == '0') {
        value = false;
    }
    else if (answer [0] == '1') {
        value = true;
    }
#endif
}

And::And (const char *name): CircuitElement (name) {
}

void And::evaluate () {
    value = inA->value && inB->value;
#ifdef debug
    cout << "AND " << name << ": " << value << endl;
#endif
}

Or::Or (const char *name): CircuitElement (name) {
}

void Or::evaluate () {
    value = inA->value || inB->value;
#ifdef debug
    cout << "OR " << name << ": " << value << endl;
#endif
}

Xor::Xor (const char *name): CircuitElement (name) {
}

void Xor::evaluate () {
    value = inA->value != inB->value;
#ifdef debug
    cout << "XOR " << name << ": " << value << endl;
#endif
}

Not::Not (const char *name): CircuitElement (name) {
}

void Not::evaluate () {
    value = !in->value;
#ifdef debug
    cout << "NOT " << name << ": " << value << endl;
#endif
}

Oneshot::Oneshot (const char *name): CircuitElement (name), oldInputValue (false) {
}
    
void Oneshot::evaluate () {
    value = in->value and !oldInputValue;
    oldInputValue = in->value;
#ifdef debug
    cout << "ONESHOT " << name << ": " << value << endl;
#endif
}

Latch::Latch (const char *name): CircuitElement (name) {
}

void Latch::evaluate () {
    if (set->value) {
        value = true;
    }
    if (reset->value) {
        value = false;
    }
#ifdef debug
    cout << "LATCH " << name << ": " << value << endl;
#endif
}

CircuitEvaluator::CircuitEvaluator (): first (0), lastSlot (&first) {
#ifdef debug
    cycleNr = 0;
#endif
}
          
void CircuitEvaluator::add (CircuitElement &element) {
    *lastSlot = &element;
    lastSlot = &element.next;
}
     
void CircuitEvaluator::evaluate () {
#ifdef debug
    cout << "CYCLE" << ++cycleNr << "\n";
#endif
    
    CircuitElement *current = first;
    while (current != 0) {
        current->evaluate ();
        current = current->next;
    }
    
#ifdef debug
    cout << "\n";
#endif
}
    
CircuitEvaluator evaluator;

void connect (CircuitElement &source, CircuitElement *&sinkInput) {
    sinkInput = &source;
}

void evaluate () {
    evaluator.evaluate ();
}

