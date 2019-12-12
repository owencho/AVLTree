#include "IntCompare.h"

int intCompare (IntNode *node, int * valuePtr){
    if(node->value < *valuePtr)
        return -1;
    else if (node->value > *valuePtr)
        return 1;
    return 0;
}

void initIntNode(IntNode * node,  IntNode * left ,IntNode * right,int balanceFactor){
    node->left = left;
    node->right = right;
    node->bFactor = balanceFactor;
}
