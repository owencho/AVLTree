#include "StringNode.h"


void initStringNode(StringNode * node,  StringNode * left ,StringNode * right,int balanceFactor){
    node->left = left;
    node->right = right;
    node->bFactor = balanceFactor;
}
