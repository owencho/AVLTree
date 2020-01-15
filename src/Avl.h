#ifndef _AVL_H
#define _AVL_H
#include "Node.h"
#include "Compare.h"
#include "AVLProcessor.h"
//Main function
Node * avlAdd(Node *root,Node * nodeAdd,Compare compare);
Node *avlDelete(Node ** root,void * nodeDelete,Compare compare);
// ADD
Node * _avlAdd(Node *root,Node * nodeAdd,int * heightInc,Compare compare);
Node * rotateLeftAndReBalanceForAdd(Node * root);
Node * rotateRightAndReBalanceForAdd(Node * root);
Node * rotateBalanceAndGetHeightChangeForAdd(Node* root,int * heightInc);
Node* nodeSearchAndAddNode(Node* root,Node * nodeAdd,int * heightInc,Compare compare);
Node* nodeSearchAndAddNodeForRight(Node* root,Node * nodeAdd,int * heightInc,Compare compare);
Node* nodeSearchAndAddNodeForLeft(Node* root,Node * nodeAdd,int * heightInc,Compare compare);
//delete
Node *_avlDelete(Node *root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare);
Node* nodeRemoveAndReplace(Node * root,int * heightDec);
Node * avlGetReplacer(Node * root ,int * heightDec,Node ** replacedNode);
Node* rotateLeftAndReBalanceForDelete(Node * root);
Node* rotateRightAndReBalanceForDelete(Node * root);
Node* nodeSearchRightForDeleteNode(Node* root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare);
Node* nodeSearchLeftForDeleteNode(Node* root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare);
Node* nodeSearchAndReplaceForDeleteNode(Node* root,void * nodeDelete,Node ** deletedNode,int * heightDec,Compare compare);
Node * rotateBalanceAndGetHeightChangeForDelete(Node* root,int * heightDec);
Node * avlRemoveSmallest(Node*root,Compare compare);
//Common function
Node * findSmallestNode(Node*root);
void visitPostOrder(Node *root, AVLProcessor processor);

#endif // _AVL_H
