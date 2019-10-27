#include "Node.h"


Node * createNode(int value,  Node * left ,Node * right,int balanceFactor){
    Node * node = malloc(sizeof(Node));
    node->value = value ;
    node->left = left;
    node->right = right;
    node->bfactor = balanceFactor;
    return node;
}
