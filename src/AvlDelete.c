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

Node *avlDelete(Node *root,void * nodeDelete,Compare compare){
    Node* deletedNode = NULL;
    Node * afterRoot;
    int height;
    afterRoot = _avlDelete(root,nodeDelete,&deletedNode,&height,compare);
    if(deletedNode == NULL){
      int*errorValue = nodeDelete;
      throwException(ERR_NODE_NOT_FOUND," node value of %d not exist inside the tree and couldnt remove the node ",*errorValue);
    }
    return afterRoot;
}

Node *_avlDelete(Node *root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare){
    Node * replacedNode = NULL;
    root = nodeSearchAndReplaceForDeleteNode(root,nodeDelete,deletedNode,heightDec,compare);
    if(root == NULL)
        return root;
    root = rotateBalanceAndGetHeightChangeForDelete(root,heightDec);
    return root;

}
//refer my samsung note for
Node * rotateBalanceAndGetHeightChangeForDelete(Node* root,int * heightDec){
    if(abs(root->bFactor) == 1 )
        *heightDec =0;
    else if(root->bFactor >= 2){
        *heightDec =(abs(root->right->bFactor) == 1);
        root = rotateLeftAndReBalanceForDelete(root);
    }
    else if(root->bFactor <= -2){
        *heightDec =(abs(root->left->bFactor) == 1);
        root = rotateRightAndReBalanceForDelete(root);
    }
    return root;
}

Node* nodeSearchAndReplaceForDeleteNode(Node* root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare){
    int size = compare(root,nodeDelete);
    if(!size){
        *deletedNode = root;
        root = nodeRemoveAndReplace(root,heightDec);
    }
    else if(size == -1)
        root = nodeSearchRightForDeleteNode(root,nodeDelete,deletedNode,heightDec,compare);
    else
        root = nodeSearchLeftForDeleteNode(root,nodeDelete,deletedNode,heightDec,compare);
    return root;
}

Node* nodeSearchRightForDeleteNode(Node* root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare){
    Node * child;
    int heightChange = 0;
    child = root->right;
    if(child != NULL){
        root->right=_avlDelete(child,nodeDelete,deletedNode,&heightChange,compare);
        *heightDec =heightChange;
        root->bFactor =root->bFactor-heightChange;
    }
    return root;
}

Node* nodeSearchLeftForDeleteNode(Node* root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare){
    Node * child;
    int heightChange = 0;
    child = root->left;
    if(child != NULL){
        root->left=_avlDelete(child,nodeDelete,deletedNode,&heightChange,compare);
        *heightDec =heightChange;
        root->bFactor =root->bFactor+heightChange;
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
      root=rotateBalanceAndGetHeightChangeForDelete(root,heightDec);
    }
    else{
      *replacedNode = root;
      *heightDec = 1;
      return root->right;
    }
    return root;
}

Node * findSmallestNode(Node*root){
    Node * leftNode;
    if(root->left != NULL){
        leftNode = root->left;
        root = findSmallestNode(leftNode);
    }
    return root;
}

Node * avlRemoveSmallest(Node*root,Compare compare){
    Node* smallestNode;
    smallestNode = findSmallestNode(root);
    void* value = smallestNode->value;
    root = avlDelete(root,value,compare);
    return smallestNode;
}
