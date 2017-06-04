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

CircuitElement::CircuitElement (const char *name): name (name), value (0), next (0) {
}

False::False (const char *name): CircuitElement (name) {
}
    
void False::evaluate () {
    value = false;
#ifdef debug
    cout << "FALSE " << name << ": " << value << endl;
#endif
}
    
True::True (const char *name): CircuitElement (name) {
}

void True::evaluate () {
    value = true;
#ifdef debug
    cout << "TRUE " << name << ": " << value << endl;
#endif
}

Input::Input (const char *name): CircuitElement (name), in (0) {
}
    
void Input::evaluate () {                                   // Input connection terminal, should have its own message c.q. LED
#ifdef debug
    if (in == 0) {                                          // Debug mode, not connected
        char answer [2];
        cout << "INPUT " << name << ": " << " ";
        cin.getline (answer, 2);                            // Only change if no 0 or 1 is typed
        if (answer [0] == '0') {
            value = false;
        }
        else if (answer [0] == '1') {
            value = true;
        }
    }
    else {                                                  // Debug mode, connected
        value = in->value;
        cout << "INPUT " << name << ": " << value << endl;
    }
#elif
    value = in->value;                                       // Non-debug mode (so always connected)
#endif
}

And::And (const char *name): CircuitElement (name), inA (0), inB (0) {
}

void And::evaluate () {
    value = inA->value && inB->value;
#ifdef debug
    cout << "AND " << name << ": " << value << endl;
#endif
}

Or::Or (const char *name): CircuitElement (name), inA (0), inB (0) {
}

void Or::evaluate () {
    value = inA->value || inB->value;
#ifdef debug
    cout << "OR " << name << ": " << value << endl;
#endif
}

Xor::Xor (const char *name): CircuitElement (name), inA (0), inB (0) {
}

void Xor::evaluate () {
    value = inA->value != inB->value;
#ifdef debug
    cout << "XOR " << name << ": " << value << endl;
#endif
}

Not::Not (const char *name): CircuitElement (name), in (0) {
}

void Not::evaluate () {
    value = !in->value;
#ifdef debug
    cout << "NOT " << name << ": " << value << endl;
#endif
}

Oneshot::Oneshot (const char *name): CircuitElement (name), in (0), oldInputValue (false) {
}
    
void Oneshot::evaluate () {
    value = in->value and !oldInputValue;
    oldInputValue = in->value;
#ifdef debug
    cout << "ONESHOT " << name << ": " << value << endl;
#endif
}

Latch::Latch (const char *name): CircuitElement (name), set (0), reset (0) {
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
