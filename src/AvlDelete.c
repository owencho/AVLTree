#include "AvlDelete.h"
#include "AvlAdd.h"
#include "Rotate.h"
#include "AvlError.h"
#include "Balance.h"
#include "Exception.h"
#include "CException.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node *avlDelete(Node ** root,void * nodeDelete,Compare compare){
    Node* deletedNode = NULL;
    Node  afterRoot;
    int height;
    if(root == NULL)
        return NULL;
    else if (nodeDelete == NULL)
        throwException(ERR_DELETE_VALUE_NULL," node does not exist inside the tree as it points to NULL");
    else if (compare==NULL )
        throwException(ERR_FN_POINTER_NULL," the function pointer for compare is NULL");

    *root = _avlDelete(*root,nodeDelete,&deletedNode,&height,compare);
    if(deletedNode == NULL){
        throwException(ERR_NODE_NOT_FOUND," node does not exist inside the tree and couldnt remove the node ");
    }
    return deletedNode;
}

Node *_avlDelete(Node *root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare){
    root = nodeSearchAndReplaceForDeleteNode(root,nodeDelete,deletedNode,heightDec,compare);
    root= rotateBalanceAndGetHeightChangeForDelete(root,heightDec);
    return root;
}

Node * rotateBalanceAndGetHeightChangeForDelete(Node* root,int * heightDec){
    if(root ==NULL || heightDec == NULL)
        return root;

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
    if(root == NULL || heightDec ==NULL || deletedNode ==NULL || nodeDelete==NULL )
        return root;
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
    if(root == NULL || heightDec ==NULL || deletedNode ==NULL || nodeDelete==NULL )
        return root;
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
    if(root == NULL || heightDec ==NULL || deletedNode ==NULL || nodeDelete==NULL)
        return root;
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
    if(root == NULL || heightDec ==NULL)
        return root;

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

Node* avlGetReplacer(Node * root ,int * heightDec,Node ** replacedNode){
    int heightChange;
    Node * newNode;
    Node * child;

    if(root == NULL || heightDec ==NULL || replacedNode ==NULL)
       return root;

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


Node* rotateLeftAndReBalanceForDelete(Node * root){
    int bFactor=0;
    int secondBfactor =0;
    if(root == NULL)
        return root;
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
    if(root == NULL)
        return root;
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

Node * findSmallestNode(Node*root){
    Node * leftNode;
    if(root == NULL)
        return NULL;
    if(root->left != NULL){
        leftNode = root->left;
        root = findSmallestNode(leftNode);
    }
    return root;
}
