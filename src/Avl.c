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

Node* rotateLeftAndReBalance(Node * root){
    root->bFactor = 0;
    if(root->right->bFactor >=0){
        root = rotateLeftNode(root);
    }else{
        root = rotateRightLeftNode(root);
    }
    root=reBalanceFactor(root);

    return root;
}

Node* rotateRightAndReBalance(Node * root){
    root->bFactor = 0;
    if(root->left->bFactor >=0){
        root = rotateLeftRightNode(root);
    }else{
        root = rotateRightNode(root);
    }
    root=reBalanceFactor(root);

    return root;
}

Node* reBalanceFactor(Node * root){
    int leftFactor =0 ;
    int rightFactor = 0 ;
    root->bFactor = 0;
    if(root->left !=NULL){
        root->left = reBalanceFactor(root->left);
        leftFactor++;
    }
    if(root->right !=NULL){
        root->right = reBalanceFactor(root->right);
        rightFactor++;
    }
    root->bFactor = rightFactor-leftFactor;
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
