#ifndef _AVLDELETE_H
#define _AVLDELETE_H
#include "Compare.h"
#include "Node.h"
Node *avlDelete(Node *root,void * nodeDelete,Compare compare);
Node *_avlDelete(Node *root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare);
Node* rotateLeftAndReBalanceForDelete(Node * root);
Node* rotateRightAndReBalanceForDelete(Node * root);
Node * avlGetReplacer(Node * root ,int * heightDec,Node ** replacedNode);
Node* nodeRemoveAndReplace(Node * root,int * heightDec);
Node* nodeSearchAndReplaceForDeleteNode(Node* root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare);
Node* nodeSearchRightForDeleteNode(Node* root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare);
Node* nodeSearchLeftForDeleteNode(Node* root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare);
Node * rotateBalanceAndGetHeightChangeForDelete(Node* root,int * heightDec);
Node * findSmallestNode(Node*root); //done
Node * avlRemoveSmallest(Node*root,Compare compare); //done
#endif // _AVLDELETE_H
