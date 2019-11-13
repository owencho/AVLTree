#include "Rotate.h"
#include "Node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node* rotateRightNode(Node * root){
      Node * leftNode = root->left;
      root->left = root->left->right;
      leftNode->right = root;
      return leftNode;
}

Node* rotateLeftNode(Node * root){
      Node * rightNode = root->right;
      root->right = root->right->left;
      rightNode->left = root;
      return rightNode;
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

/*
Node* rotateLeftRightNode(Node * root){
      //Rotate LEFT
      Node * rightNode = root->left->right;
      root->left->right = root->left->right->left;
      rightNode->left = root->left;
      root->left = rightNode;
      //Rotate rIGHT
      Node * leftNode = root->left;
      root->left = root->left->right;
      leftNode->right = root;
      return leftNode;

}

Node* rotateRightLeftNode(Node * root){
      Node* x = rotateRightNode(root->right);
      root->right = x ;
      return rotateLeftNode(root);
}
*/
