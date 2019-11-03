#ifndef _AVL_H
#define _AVL_H

#include "Node.h"
Node *avlAdd(Node *root,Node * nodeAdd);
Node * _avlAdd(Node *root,Node * nodeAdd,int * heightInc);
Node* reBalanceFactor(Node * root);
Node * rotateLeftAndReBalance(Node * root);
Node *rotateRightAndReBalance(Node * root);
#endif // _AVL_H
