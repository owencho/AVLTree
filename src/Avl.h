#ifndef _AVL_H
#define _AVL_H

#include "Node.h"
Node *avlAdd(Node *root,Node * nodeAdd);
Node * _avlAdd(Node *root,Node * nodeAdd,int * heightInc);
#endif // _AVL_H
