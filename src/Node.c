#include "Node.h"
#include <stdlib.h>

Node * createNode(int value,  Node * left ,Node * right,int balanceFactor){
    Node * node = malloc(sizeof(Node));
    node->value = value ;
    node->left = left;
    node->right = right;
    node->bFactor = balanceFactor;
    return node;
}

void initNode(Node * node,  Node * left ,Node * right,int balanceFactor){
    node->left = left;
    node->right = right;
    node->bFactor = balanceFactor;
}
