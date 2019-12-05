#ifndef _AVLDELETE_H
#define _AVLDELETE_H

#include "Node.h"
Node *avlDelete(Node *root,int nodeDelete);
Node *_avlDelete(Node *root,int nodeDelete,Node ** deletedNode,int * heightDec);
Node* rotateLeftAndReBalanceForDelete(Node * root);
Node* rotateRightAndReBalanceForDelete(Node * root);
Node * avlGetReplacer(Node * root ,int * heightDec,Node ** replacedNode);
Node* nodeRemoveAndReplace(Node * root,int * heightDec);
Node* nodeSearchforDeleteNode(Node* root,int nodeDelete,Node ** deletedNode,int * heightDec);
Node * rotateBalanceAndGetHeightChangeForDelete(Node* root,int * heightDec);
#endif // _AVLDELETE_H
