#include "Avl.h"
#include "Rotate.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Node *avlAdd(Node *root,Node * nodeAdd){
  int heightInc;
  nodeAdd->left = NULL;
  nodeAdd->right = NULL;
  nodeAdd->bFactor =0;
  return _avlAdd(root,nodeAdd,&heightInc);
}
Node *_avlAdd(Node *root,Node * nodeAdd,int * heightInc){
    int bfact = 0;
    Node * child;
    if(root->value < nodeAdd->value){
        child = root->right;
        if(child == NULL){
            root->bFactor++;
            root->right = nodeAdd;
            *heightInc =1;
        }else{
            root->right=_avlAdd(child,nodeAdd,&bfact);
            if(bfact ==1){
              *heightInc =1;
            }
            root->bFactor =root->bFactor+bfact;
        }
    }
    else{
        child = root->left;
        if(child == NULL){
            root->bFactor --;
            root->left = nodeAdd;
            *heightInc =1;
        }else{
            root->left=_avlAdd(child,nodeAdd,&bfact);
            if(bfact ==1){
              *heightInc =1;
            }
            root->bFactor =root->bFactor-bfact;

        }
    }

    if(root->bFactor >= 2){
        child = root->right;
        if(child->bFactor >=0){
            root = rotateLeftNode(root);
        }else{
            root = rotateRightLeftNode(root);
        }
    }else if(root->bFactor <= -2){
        child = root->left;
        if(child->bFactor >=0){
            root = rotateLeftRightNode(root);
        }else{
            root = rotateRightNode(root);
        }
    }
    return root;

}

Node* rotateLeftAndReBalance(Node * root){
    root->bFactor = 0;
    if(root->right->bFactor >=0){
        root = rotateLeftNode(root);
    }else{
        root = rotateRightLeftNode(root);
    }
    root->bFactor = 0;

}
