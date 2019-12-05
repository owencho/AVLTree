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
    Node * replacedNode = NULL;
    if (root->value ==nodeDelete){
        *deletedNode = root;
        root = nodeRemoveAndReplace(root,heightDec);
        if(root == NULL)
            return root;
    }
    else{
        root = nodeSearchforDeleteNode(root,nodeDelete,deletedNode,heightDec);
    }

    root = rotateBalanceAndGetHeightChange(root,heightDec);
    return root;

}

Node * rotateBalanceAndGetHeightChange(Node* root,int * heightDec){
    if(abs(root->bFactor) == 1 )
        *heightDec =0;
    else if(root->bFactor >= 2){
        root = rotateLeftAndReBalanceForDelete(root);
        *heightDec =0;
    }
    else if(root->bFactor <= -2){
        root = rotateRightAndReBalanceForDelete(root);
        *heightDec =0;
    }
    return root;
}

Node* nodeSearchforDeleteNode(Node* root,int nodeDelete,Node ** deletedNode,int * heightDec){
    Node * child;
    int heightChange = 0;
    if(root->value < nodeDelete){
        child = root->right;
        if(child != NULL){
            root->right=_avlDelete(child,nodeDelete,deletedNode,&heightChange);
            *heightDec =heightChange;
            root->bFactor =root->bFactor-heightChange;
        }
    }
    else{
        child = root->left;
        if(child != NULL){
            root->left=_avlDelete(child,nodeDelete,deletedNode,&heightChange);
            *heightDec =heightChange;
            root->bFactor =root->bFactor+heightChange;
        }
    }
    return root;
}

Node* nodeRemoveAndReplace(Node * root,int * heightDec){
    int rootBFactor;
    int heightChange = 0;
    Node * rootLeft;
    Node * replacedNode;
    if(root->right == NULL){
        *heightDec =1;
        return root->left;
    }
    else{
        rootLeft = root->left;
        rootBFactor = root->bFactor;
        root= avlGetReplacer(root->right,&heightChange,&replacedNode);
        *heightDec =heightChange;
        replacedNode->left = rootLeft;
        replacedNode->right = root;
        replacedNode->bFactor =rootBFactor-heightChange;
        root = replacedNode;
    }
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

Node* avlGetReplacer(Node * root ,int * heightDec,Node ** replacedNode){
    int heightChange;
    Node * newNode;
    Node * child;
    if(root->left != NULL){
      child = avlGetReplacer(root->left ,&heightChange,&newNode);
      *replacedNode = newNode;
      *heightDec =heightChange;
      root->bFactor =root->bFactor+heightChange;
      root->left = child;
      root=rotateBalanceAndGetHeightChange(root,heightDec);
    }
    else{
      *replacedNode = root;
      *heightDec = 1;
      return root->right;
    }
    return root;
}
