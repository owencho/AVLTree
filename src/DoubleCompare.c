#include "DoubleCompare.h"

int doubleCompare (DoubleNode *node, double * valuePtr){
    if(node->value < *valuePtr)
        return -1;
    else if (node->value > *valuePtr)
        return 1;
    return 0;
}
