#include "Rotate.h"
#include "Node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node* rotateRightNode(Node * root){
      Node * rightNode = root->left;
      root->left = root->left->right;
      rightNode->right = root;
      return rightNode;
}

Node* rotateLeftNode(Node * root){
      Node * leftNode = root->right;
      root->right = root->right->left;
      leftNode->left = root;
      return leftNode;
}

Node* rotateLeftRightNode(Node * root){
      Node* x = rotateLeftNode(root->left);
      root->left = x ;
      return rotateRightNode(root);
}

Node* rotateRightLeftNode(Node * root){
      Node* x = rotateRightNode(root->right);
      root->right = x ;
      return rotateLeftNode(root);
}
