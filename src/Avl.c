#include "Avl.h"
#include "Rotate.h"
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
        root = rotateLeftAndReBalance(root);
        *heightInc =0;
    }else if(root->bFactor <= -2){
        root = rotateRightAndReBalance(root);
        *heightInc =0;
    }
    return root;

}
//fix this for poh teach last wednes 15/11
Node* rotateLeftAndReBalance(Node * root){
    int bFactor=0;
    if(root->right->bFactor >=0){
        bFactor = root->right->right->bFactor;
        root = rotateLeftNode(root);
    }else{
        bFactor = root->right->left->bFactor;
        root = rotateRightLeftNode(root);
    }
  //fix this  root->bFactor = (0-[(rightLeftBfactor-)])
    return root;
}

Node* rotateRightAndReBalance(Node * root){
    root->bFactor = 0;
    if(root->left->bFactor >=0){
        root = rotateLeftRightNode(root);
        root->left->bFactor =0;
    }else{
        root = rotateRightNode(root);
    }
    root->right->bFactor =0;
    root->bFactor =0;
    return root;
}

void freeAllNodesInTree(Node *root){
    if(root->left != NULL){
        freeAllNodesInTree(root->left);
    }
    if (root->right != NULL){
        freeAllNodesInTree(root->right);
    }
    freeNode(root);
}
