#ifndef _AVLDELETE_H
#define _AVLDELETE_H

#include "Node.h"
Node *avlDelete(Node *root,int nodeDelete);
Node *_avlDelete(Node *root,int nodeDelete,Node ** deletedNode,int * heightDec);
Node* rotateLeftAndReBalanceDelete(Node * root);
Node* rotateRightAndReBalanceDelete(Node * root);
#endif // _AVLDELETE_H
