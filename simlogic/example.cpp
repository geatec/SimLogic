#include "simlogic.h"

int main  () {
    create (Button, button0);
    create (Button, button1);
    create (And, and0);
    create (Not, not0);

    connect (button0, and0.input0);
    connect (button1, and0.input1);
    connect (and0, not0.input);

    for (;;) {  // Forever loop, idiomatic since K&R C
        // All Arduino digitalRead's go here
        
        // Evaluate interconnected circuit once
        evaluate ();
        
        // All Arduino digitalWrite's go here
    }
    
    return 0;
}
