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
        if(root->right == NULL){
          root->right = nodeAdd;
          root->bFactor++;
        }
        else{
          root->right=_avlAdd(child,nodeAdd,heightInc);
          root->bFactor += *heightInc;
        }
    }
    return root;

}
/*
Node *_avlAdd(Node *root,Node * nodeAdd,int * heightInc){
    int bfact = 0;
    Node * child;
    if(root->value < nodeAdd->value){
        child = root->right;
        if(child == NULL){
            root->bFactor++;
            root->right = nodeAdd;
        }else{
            root->right=_avlAdd(child,nodeAdd,heightInc);
            root->bFactor += bfact;

        }
    }
    else{
        child = root->left;
        if(child == NULL){
            root->bFactor--;
            root->left = nodeAdd;
        }else{
            root->left=_avlAdd(child,nodeAdd,heightInc);
            root->bFactor -= bfact;
        }
    }

    if(root->bFactor >= 2){
        child = root->right;
        if(child->bFactor >=0){
            root = rotateLeftNode(root);
        }else{
            root = rotateRightLeftNode(root);
        }
    }
    return root;

}
*/
