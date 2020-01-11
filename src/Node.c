#include "Node.h"
#include <stdlib.h>

void freeAllNodesInTree(Node *root){
    if(root == NULL) return; 
    if(root->left != NULL){
        freeAllNodesInTree(root->left);
    }
    if (root->right != NULL){
        freeAllNodesInTree(root->right);
    }
    freeNode(root);
}
