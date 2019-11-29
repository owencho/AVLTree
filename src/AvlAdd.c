#include "AvlAdd.h"
#include "Rotate.h"
#include "Balance.h"
#include "Error.h"
#include "Exception.h"
#include "CException.h"
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
    if(root->value == nodeAdd->value){
      throwException(ERR_SAME_NODE,"same node value detected");
    }
    else if(root->value < nodeAdd->value){
        child = root->right;
        if(child == NULL){
            root->bFactor++;
            root->right = nodeAdd;
            *heightInc =1;
        }else{
            root->right=_avlAdd(child,nodeAdd,&bfact);
            *heightInc =bfact;
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
            *heightInc =bfact;
            root->bFactor =root->bFactor-bfact;
        }
    }
    if(root->bFactor == 0 ){
      *heightInc =0;
    }else if(root->bFactor >= 2){
      root = rotateLeftAndReBalanceForAdd(root);
      *heightInc =0;
    }else if(root->bFactor <= -2){
      root = rotateRightAndReBalanceForAdd(root);
      *heightInc =0;
    }
    return root;
}


Node* rotateLeftAndReBalanceForAdd(Node * root){
    int bFactor=0;
    if(root->right->bFactor >=0){
        bFactor = root->right->right->bFactor;
        root = rotateLeftNode(root);
        root->left->bFactor = 0;
        root->right->bFactor = bFactor;
    }else{
        bFactor = root->right->left->bFactor;
        root = rotateRightLeftNode(root);
        root = balanceForDoubleRotate(root,bFactor);
    }
    root->bFactor = 0;
    return root;
}

Node* rotateRightAndReBalanceForAdd(Node * root){
    int bFactor=0;
    if(root->left->bFactor >0){
        bFactor = root->left->right->bFactor;
        root = rotateLeftRightNode(root);
        root = balanceForDoubleRotate(root ,bFactor);
    }else{
        bFactor = root->left->left->bFactor;
        root = rotateRightNode(root);
        root->right->bFactor = 0;
        root->left->bFactor = bFactor;
    }
    root->bFactor =0;
    return root;
}
