#include "Rotate.h"
#include "Node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node* rotateRightNode(Node * root){
      Node * rightNode = createNode(root->left->value, root->left->left ,NULL);
      root->left = NULL;
      rightNode->right = root;
      return rightNode;
}

Node* rotateLeftNode(Node * root){
      Node * leftNode = createNode(root->right->value,  NULL ,root->right->right);
      root->right = NULL;
      leftNode->left = root;
      return leftNode;
}

Node* rotateLeftRightNode(Node * root){
      Node* x = rotateLeftNode(root->left);
      Node * y = createNode(root->value,x,NULL);
      return rotateRightNode(y);
}

Node* rotateRightLeftNode(Node * root){
      Node* x = rotateRightNode(root->right);
      Node * y = createNode(root->value,  NULL ,x);
      return rotateLeftNode(y);
}
