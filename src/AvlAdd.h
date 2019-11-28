#ifndef _AVLADD_H
#define _AVLADD_H
#include "Node.h"
Node * avlAdd(Node *root,Node * nodeAdd);
Node * _avlAdd(Node *root,Node * nodeAdd,int * heightInc);
Node * rotateLeftAndReBalanceForAdd(Node * root);
Node * rotateRightAndReBalanceForAdd(Node * root);
#endif // _AVLADD_H
