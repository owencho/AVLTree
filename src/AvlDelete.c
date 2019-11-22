#include "AvlDelete.h"
#include "AvlAdd.h"
#include "Rotate.h"
#include "Error.h"
#include "Exception.h"
#include "CException.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node *avlDelete(Node *root,int nodeDelete){
    Node* deletedNode = NULL;
    Node * afterRoot;
    int height;
    afterRoot = _avlDelete(root,nodeDelete,&deletedNode,&height);
    if(deletedNode == NULL){
      throwException(ERR_NODE_NOT_FOUND," node value of %d cant found inside the tree and couldnt remove the node ",nodeDelete);
    }
    return afterRoot;
}

Node *_avlDelete(Node *root,int nodeDelete,Node ** deletedNode,int * heightDec){
    Node * child;
    int bfact = 0;
    if(root->value < nodeDelete){
        child = root->right;
        if(child != NULL){
            root->right=_avlDelete(child,nodeDelete,deletedNode,&bfact);
            if(bfact ==1 ){
              *heightDec =1;
              root->bFactor =root->bFactor-bfact;
            }
        }
    }
    else if (root->value ==nodeDelete){
        *deletedNode = root;
        *heightDec =1;
        return NULL;
    }
    else{
        child = root->left;
        if(child != NULL){
            root->left=_avlDelete(child,nodeDelete,deletedNode,&bfact);
            if(bfact ==1 ){
              *heightDec =1;
              root->bFactor =root->bFactor+bfact;
            }
        }
    }
    if((root->bFactor == -1 )||root->bFactor == 1 ){
        *heightDec =0;
    }else if(root->bFactor >= 2){
        root = rotateLeftAndReBalanceDelete(root);
        *heightDec =0;
    }else if(root->bFactor <= -2){
        root = rotateRightAndReBalanceDelete(root);
        *heightDec =0;
    }
    return root;

}

Node* rotateLeftAndReBalanceDelete(Node * root){
    int bFactor=0;
    int secondBfactor =0;
    if(root->right->bFactor >=0){
        bFactor = root->right->bFactor;
        secondBfactor = root->right->right->bFactor;
        root = rotateLeftNode(root);
        root->bFactor = bFactor -1;
        root->left->bFactor = !bFactor;
        root->right->bFactor = secondBfactor;
    }else{
        bFactor = root->right->left->bFactor;
        root = rotateRightLeftNode(root);
        root->bFactor = 0;
        root->left->bFactor = (-1-(bFactor-1)>>1)*(bFactor&1);
        root->right->bFactor = (0-(bFactor-1)>>1)*(bFactor&1);
    }
    return root;
}

Node* rotateRightAndReBalanceDelete(Node * root){
    int bFactor=0;
    if(root->left->bFactor >=0){
        bFactor = root->left->right->bFactor;
        root = rotateLeftRightNode(root);
        root->left->bFactor = (-1-(bFactor-1)>>1)*(bFactor&1);
        root->right->bFactor = (0-(bFactor-1)>>1)*(bFactor&1);
    }else{
        bFactor = root->left->left->bFactor;
        root = rotateRightNode(root);
        root->right->bFactor = 0;
        root->left->bFactor = bFactor;
    }
    root->bFactor =0;
    return root;
}
