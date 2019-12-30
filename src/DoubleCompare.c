#include "DoubleCompare.h"

int doubleCompareForAvlAdd (DoubleNode *node, DoubleNode *nodeAdd){
    if(node->value < nodeAdd->value)
        return -1;
    else if (node->value > nodeAdd->value)
        return 1;
    return 0;
}
int doubleCompareForAvlDelete (DoubleNode *node, double * valuePtr){
    if(node->value < *valuePtr)
        return -1;
    else if (node->value > *valuePtr)
        return 1;
    return 0;
}
