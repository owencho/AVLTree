#include "AvlDelete.h"
#include "Rotate.h"
#include "Error.h"
#include "Exception.h"
#include "CException.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
Node *avlDelete(Node *root,int nodeDelete){
    Node* deletedNode;
    Node * afterRoot;
    afterRoot = _avlDelete(root,nodeDelete,&deletedNode);
    if(deletedNode == NULL){
      throwException(ERR_SAME_NODE," node value of %d cant found inside the tree ",nodeDelete);
    }
    return afterRoot;
}

Node *_avlDelete(Node *root,int nodeDelete,Node ** deletedNode,int * heightInc){
    Node * child;
    int bfact;
    if(root->value < nodeDelete){
        child = root->right;
        if(child != NULL){
            root->right=_avlDelete(child,nodeDelete,deletedNode,&bfact);
        }
        else if (child->value ==nodeDelete){
          *deletedNode = root;
          *heightInc =1;
        }
    }
    else{
        child = root->left;
        if(child != NULL){
            root->left=_avlDelete(child,nodeDelete,deletedNode);
        }
    }
    if(root->bFactor == 0 ){
        *heightDec =0;
    }else if(root->bFactor >= 2){
      //  root = rotateLeftAndReBalanceDelete(root);
        *heightDec =0;
    }else if(root->bFactor <= -2){
    //    root = rotateRightAndReBalanceDelete(root);
        *heightDec =0;
    }
    return root;

}
*/
