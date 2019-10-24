#include "Node.h"


Node * createNode(int value,  Node * left ,Node * right){
    Node * node = malloc(sizeof(Node));
    node->value = value ;
    node->left = left;
    node->right = right;
    return node;
}
