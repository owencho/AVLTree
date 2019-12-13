#include "IntNode.h"

void initIntNode(IntNode * node,  IntNode * left ,IntNode * right,int balanceFactor){
    node->left = left;
    node->right = right;
    node->bFactor = balanceFactor;
}
