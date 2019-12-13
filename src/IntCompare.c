#include "IntCompare.h"
#include "IntNode.h"
int intCompare (IntNode *node, int * valuePtr){
    if(node->value < *valuePtr)
        return -1;
    else if (node->value > *valuePtr)
        return 1;
    return 0;
}
