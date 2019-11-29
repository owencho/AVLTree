#include "AvlDelete.h"
#include "AvlAdd.h"
#include "Rotate.h"
#include "Error.h"
#include "Balance.h"
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
    Node * rootLeft;
    Node * replacedNode;
    int bfact = 0;
    if(root->value < nodeDelete){
        child = root->right;
        if(child != NULL){
            root->right=_avlDelete(child,nodeDelete,deletedNode,&bfact);
            *heightDec =bfact;
            root->bFactor =root->bFactor-bfact;
        }
    }
    else if (root->value ==nodeDelete){
        *deletedNode = root;
        *heightDec =1;
        if(root->right == NULL){
            return root->left;
        }
        else{
            rootLeft = root->left;
            //root= avlGetReplacer(root->right,heightDec,&replacedNode);
            root->left = rootLeft;
            return root;
        }
    }
    else{
        child = root->left;
        if(child != NULL){
            root->left=_avlDelete(child,nodeDelete,deletedNode,&bfact);
            *heightDec =bfact;
            root->bFactor =root->bFactor+bfact;
        }
    }
    *heightDec = !(abs(root->bFactor) == 1||(root->bFactor >= 2||root->bFactor <= -2 ));
    if(root->bFactor >= 2)
        root = rotateLeftAndReBalanceForDelete(root);
    else if(root->bFactor <= -2)
        root = rotateRightAndReBalanceForDelete(root);

    return root;

}

Node* rotateLeftAndReBalanceForDelete(Node * root){
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
        root = balanceForDoubleRotate(root ,bFactor);
    }
    return root;
}

Node* rotateRightAndReBalanceForDelete(Node * root){
    int bFactor=0;
    int secondBfactor =0;
    if(root->left->bFactor > 0){
        bFactor = root->left->right->bFactor;
        root = rotateLeftRightNode(root);
        root = balanceForDoubleRotate(root ,bFactor);
    }else{
        bFactor = root->left->bFactor;
        secondBfactor = root->left->left->bFactor;
        root = rotateRightNode(root);
        root->right->bFactor = -1-bFactor;
        root->left->bFactor = secondBfactor;
        root->bFactor =1+bFactor;
    }
    return root;
}
/*
Node* avlGetReplacer(Node * root ,int * heightDec,Node ** replacedNode){

}
*/
