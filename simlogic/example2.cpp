#include "simlogic.h"

int main  () {
    create (Button, set);
    create (Button, reset);
    create (Latch, latch);
    create (Oneshot, oneshot);

    connect (set, latch.set);
    connect (reset, latch.reset);
    connect (latch, oneshot.input);

    for (;;) {  // Forever loop, idiomatic since K&R C
        // All Arduino digitalRead's go here
        
        // Evaluate interconnected circuit once
        evaluate ();
        
        // All Arduino digitalWrite's go here
    }
    
    return 0;
}
