#include "simlogic.h"

#ifdef debug   // Don't generate any IO code for a single board computer
#include <iostream>
using namespace std;
#endif

CircuitElement::CircuitElement (const char *name): name (name), next (0) {
}

Button::Button (const char *name): CircuitElement (name) {
}
    
void Button::evaluate () {
#ifdef debug
    char answer;
    cout << "BUTTON " << name << " <1/0>: ";
    cin >> answer;
    value = answer == '1';
#endif
}

And::And (const char *name): CircuitElement (name) {
}

void And::evaluate () {
    value = input0->value && input1->value;
#ifdef debug
    cout << "AND " << name << ": " << value << endl;
#endif
}

Or::Or (const char *name): CircuitElement (name) {
}

void Or::evaluate () {
    value = input0->value || input1->value;
#ifdef debug
    cout << "OR " << name << ": " << value << endl;
#endif
}

Xor::Xor (const char *name): CircuitElement (name) {
}

void Xor::evaluate () {
    value = input0->value != input1->value;
#ifdef debug
    cout << "XOR " << name << ": " << value << endl;
#endif
}

Not::Not (const char *name): CircuitElement (name) {
}

void Not::evaluate () {
    value = !input->value;
#ifdef debug
    cout << "NOT " << name << ": " << value << endl;
#endif
}

Oneshot::Oneshot (const char *name): CircuitElement (name), oldInputValue (false) {
}
    
void Oneshot::evaluate () {
    value = input->value and !oldInputValue;
    oldInputValue = input->value;
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

