/*
Understanding this header requires understanding some C++
But using it merely requires C knowledge
*/

struct CircuitElement {
    bool value;
    const char *name;
    CircuitElement *next;
    
    CircuitElement (const char *name);    
    virtual void evaluate () = 0;       
};

struct Button: CircuitElement {
    Button (const char *name);
    void evaluate ();
};

struct And: CircuitElement {
    CircuitElement *input0, *input1;
    
    And (const char *name);
    void evaluate ();
};

struct Or: CircuitElement  {
    CircuitElement *input0, *input1;    
    Or (const char *name);
    void evaluate ();
};

struct Xor: CircuitElement  {
    CircuitElement *input0, *input1;    
    
    Xor (const char *name);
    void evaluate ();
};

struct Not: CircuitElement  {
    CircuitElement *input;
    
    Not (const char *name);
    void evaluate ();
};

struct Oneshot: CircuitElement  {
    CircuitElement *input;
    bool oldInputValue;
    
    Oneshot (const char *name);
    void evaluate ();
};

struct Latch: CircuitElement  {
    CircuitElement *set, *reset;
    
    Latch (const char *name);
    void evaluate ();
};

struct CircuitEvaluator {
    CircuitElement *first, **lastSlot;
#ifdef debug
    int cycleNr;
#endif
    
    CircuitEvaluator ();
    void add (CircuitElement &element);
    void evaluate ();
};

extern CircuitEvaluator evaluator;

#define create(type, name) type name (#name); evaluator.add (name)
extern void connect (CircuitElement &source, CircuitElement *&sinkInput);
extern void evaluate ();
