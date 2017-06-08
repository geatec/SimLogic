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

#ifdef __arduino__

#ifdef __debug__
SerialStream &SerialStream::operator<< (const char * const data) {
    Serial.write (data);
    Serial.flush ();
    return *this;
}

SerialStream &SerialStream::operator<< (bool data) {
    return this->operator<< (data ? "true" : "false");
}

SerialStream &SerialStream::operator<< (int data) {
    static char chars [256];
    itoa (data, chars, 10);
    return this->operator<< (chars);
}

SerialStream &SerialStream::operator>> (char * const data) {
    int index = 0;
    for (;;) {
        delay (10);
        if (Serial.available ()){
            data [index] = Serial.read ();
            Serial.print (data [index]);
            if (data [index] == '\n') {
                data [index] = (char) 0;
                break;
            }
            index++;
        }
    }
    return *this;
}

SerialStream cin, cout;

const char * const endl = "\n";
#endif
#else
#endif

CircuitElement::CircuitElement (const char * const name): name (name), value (0), next (0) {
}

False::False (const char * const name): CircuitElement (name) {
}
    
void False::evaluate () {
    value = false;
#ifdef __debug__
    cout << "FALSE " << name << ": " << value << endl;
#endif
}
    
True::True (const char * const name): CircuitElement (name) {
}

void True::evaluate () {
    value = true;
#ifdef __debug__
    cout << "TRUE " << name << ": " << value << endl;
#endif
}

Input::Input (const char * const name): CircuitElement (name), in (0) {
}
    
void Input::evaluate () {                                   // Input connection terminal, should have its own message c.q. LED
#ifdef __debug__
    if (in == 0) {                                          // __debug__ mode, not connected
        char answer [2];
        cout << "INPUT " << name << ": " << " ";
        cin >> answer;
        if (answer [0] == '0') {
            value = false;
        }
        else if (answer [0] == '1') {
            value = true;
        }
    }
    else {                                                  // __debug__ mode, connected
        value = in->value;
        cout << "INPUT " << name << ": " << value << endl;
    }
#endif
}

And::And (const char * const name): CircuitElement (name), inA (0), inB (0) {
}

void And::evaluate () {
    value = inA->value && inB->value;
#ifdef __debug__
    cout << "AND " << name << ": " << value << endl;
#endif
}

Or::Or (const char * const name): CircuitElement (name), inA (0), inB (0) {
}

void Or::evaluate () {
    value = inA->value || inB->value;
#ifdef __debug__
    cout << "OR " << name << ": " << value << endl;
#endif
}

Xor::Xor (const char * const name): CircuitElement (name), inA (0), inB (0) {
}

void Xor::evaluate () {
    value = inA->value != inB->value;
#ifdef __debug__
    cout << "XOR " << name << ": " << value << endl;
#endif
}

Not::Not (const char * const name): CircuitElement (name), in (0) {
}

void Not::evaluate () {
    value = !in->value;
#ifdef __debug__
    cout << "NOT " << name << ": " << value << endl;
#endif
}

Oneshot::Oneshot (const char * const name): CircuitElement (name), in (0), oldInputValue (false) {
}
    
void Oneshot::evaluate () {
    value = in->value and !oldInputValue;
    oldInputValue = in->value;
#ifdef __debug__
    cout << "ONESHOT " << name << ": " << value << endl;
#endif
}

Latch::Latch (const char * const name): CircuitElement (name), set (0), reset (0) {
}

void Latch::evaluate () {
    if (set->value) {
        value = true;
    }
    if (reset->value) {
        value = false;
    }
#ifdef __debug__
    cout << "LATCH " << name << ": " << value << endl;
#endif
}

CircuitEvaluator::CircuitEvaluator (): first (0), lastSlot (&first) {
#ifdef __debug__
    cycleNr = 0;
#endif
}
          
void CircuitEvaluator::add (CircuitElement &element) {
    *lastSlot = &element;
    lastSlot = &element.next;
}
     
void CircuitEvaluator::evaluate () {
#ifdef __debug__
    cout << "CYCLE" << ++cycleNr << "\n";
#endif    
    CircuitElement *current = first;
    while (current != 0) {
        current->evaluate ();
        current = current->next;
    }
#ifdef __debug__
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
