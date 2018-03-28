#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "binomial.h"
#include "integer.h"

int
main(void)
{ 
    BINOMIAL * bin = newBINOMIAL(displayINTEGER, compareINTEGER, swapINTEGER, freeINTEGER);
    insertBINOMIAL(bin, newINTEGER(3));
    insertBINOMIAL(bin, newINTEGER(5));
    insertBINOMIAL(bin, newINTEGER(1));
    displayBINOMIAL(bin, stdout);
    statisticsBINOMIAL(bin, stdout);
}
