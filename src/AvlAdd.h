#ifndef _AVLADD_H
#define _AVLADD_H
#include "Node.h"
Node * avlAdd(Node *root,Node * nodeAdd,Compare compare);
Node * _avlAdd(Node *root,Node * nodeAdd,int * heightInc,Compare compare);
Node * rotateLeftAndReBalanceForAdd(Node * root);
Node * rotateRightAndReBalanceForAdd(Node * root);
Node * rotateBalanceAndGetHeightChangeForAdd(Node* root,int * heightInc);
Node* nodeSearchAndAddNode(Node* root,Node * nodeAdd,int * heightInc,Compare compare);
#endif // _AVLADD_H
