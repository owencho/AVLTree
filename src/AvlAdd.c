#include "AvlAdd.h"
#include "Rotate.h"
#include "Balance.h"
#include "Error.h"
#include "Exception.h"
#include "CException.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Node *avlAdd(Node *root,Node * nodeAdd,Compare compare){
    int heightInc;
    nodeAdd->left = NULL;
    nodeAdd->right = NULL;
    nodeAdd->bFactor =0;
    return _avlAdd(root,nodeAdd,&heightInc,compare);
}
Node *_avlAdd(Node *root,Node * nodeAdd,int * heightInc,Compare compare){
    root = nodeSearchAndAddNode(root,nodeAdd,heightInc,compare);
    root = rotateBalanceAndGetHeightChangeForAdd(root,heightInc);
    return root;
}

Node* nodeSearchAndAddNode(Node* root,Node * nodeAdd,int * heightInc,Compare compare){
    Node * child;
    int heightChange=0;
    int size = compare(root,(void*)&nodeAdd->value);
    if(!size)
        throwException(ERR_SAME_NODE,"same node value detected");
    else if(size == -1){
        child = root->right;
        if(child == NULL){
            root->bFactor++;
            root->right = nodeAdd;
            *heightInc =1;
        }else{
            root->right=_avlAdd(child,nodeAdd,&heightChange,compare);
            *heightInc =heightChange;
            root->bFactor =root->bFactor+heightChange;
        }
    }
    else{
        child = root->left;
        if(child == NULL){
            root->bFactor --;
            root->left = nodeAdd;
            *heightInc =1;
        }else{
            root->left=_avlAdd(child,nodeAdd,&heightChange,compare);
            *heightInc =heightChange;
            root->bFactor =root->bFactor-heightChange;
        }
    }
    return root;
}

Node * rotateBalanceAndGetHeightChangeForAdd(Node* root,int * heightInc){
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
