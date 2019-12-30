#include "IntCompare.h"
#include "IntNode.h"
int intCompareForAvlAdd (IntNode *node, IntNode * nodeAdd){
    if(node->value < nodeAdd->value)
        return -1;
    else if (node->value > nodeAdd->value)
        return 1;
    return 0;
}

int intCompareForAvlDelete (IntNode *node, int * nodeDelete){
    if(node->value < *nodeDelete)
        return -1;
    else if (node->value > *nodeDelete)
        return 1;
    return 0;
}
