#include "DoubleNode.h"

void initDoubleNode(DoubleNode * node,  DoubleNode * left ,DoubleNode * right,int balanceFactor){
    node->left = left;
    node->right = right;
    node->bFactor = balanceFactor;
}
