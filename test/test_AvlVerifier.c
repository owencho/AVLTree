#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "unity.h"
#include "AvlVerifier.h"
#include "Compare.h"
#include "IntCompare.h"
#include "IntNode.h"
#include "Balance.h"
#include "AvlAdd.h"
#include "Balance.h"
#include "AvlDelete.h"
#include "Node.h"
#include "CustomAssert.h"
#include "Rotate.h"
#include "Exception.h"
#include "Error.h"
#include "CException.h"

CEXCEPTION_T ex;
void setUp(void){}
void tearDown(void){}

Node * createNode(uint32_t value){
    IntNode * node = malloc(sizeof(IntNode));
    node->value = value ;
    node->left = NULL;
    node->right = NULL;
    node->bFactor = 0;
    return (Node*)node;
}
Node *createAvlNode(uint32_t value){
    IntNode * node =(IntNode*)malloc(sizeof(IntNode));
    node->value =value;
    node->bFactor = 1;
    node ->left = (IntNode*)1;
    node ->right = (IntNode*)1;

    return (Node*)node;
}

uint32_t getRandomNum(void){
    return rand() + (rand() << 15) + (rand() << 30) ;
}

void test_random_num(void){
    int i =10;
    srand(time(0)); //different value everytime you run
    while(i--)
        printf("random num : %d \n",getRandomNum());
}
int getRandomDeleteNode(IntNode* childNode, int height){
    int randNum;
    while(height--){
        randNum = getRandomNum();
        if(randNum > childNode->value ){
            if(childNode->right != NULL)
                childNode=childNode->right;
            else if (childNode-> left != NULL)
                childNode=childNode->left;
            else{
                break;
            }
        }
        else if(randNum < childNode->value ){
            if(childNode->left != NULL)
                childNode=childNode->left;
            else if (childNode-> right != NULL)
                childNode=childNode->right;
            else{
                break;
            }
        }
        else {
            break;
        }
    }
    return childNode->value;
}
//srand(2)
//5 √ 10 √ 100 √ 1000 √ 10000 √
//time(0)
//5 √ 10 √ 100 √ 1000 √ 10000 √

//Automated Test for checking AVL add function

void test_verify_AVL_tree(void){
    Node * root;
    int max = 100000 , i;
    srand(time(0));
    i = max;
    root =  createNode(getRandomNum());
    while(i--){
       Try{
            root = avlAdd(root,createAvlNode(getRandomNum()),(Compare)intCompareForAvlAdd);
        }Catch(ex){
            dumpException(ex);
            i++;
        }
        TEST_VERIFY_AVL_TREE((IntNode*)root, max-i+1);
    }
    freeAllNodesInTree(root);
}

//Automated Test for checking AVL add and delete function
void test_verify_add_delete_AVL_tree(void){
    Node * root ;
    IntNode * deletedNode;
    Node * childNode;
    int max = 100 , i;
    int height,deleteValue;
    srand(time(0));
    i = max;
    root =  createNode(getRandomNum());
    while(i--){
       Try{
            root = avlAdd(root,createAvlNode(getRandomNum()),(Compare)intCompareForAvlAdd);
        }Catch(ex){
            dumpException(ex);
            i++;
        }
        TEST_VERIFY_AVL_TREE((IntNode*)root, max-i+1);
    }
    for(i=0;i<max;i++){
        height= (getRandomNum()/(log2(max)+5));
        deleteValue=getRandomDeleteNode((IntNode*)root,height);

         Try{
              deletedNode = (IntNode*)avlDelete(&root,(void*)&deleteValue,(Compare)intCompareForAvlDelete);
              freeNode((Node*)deletedNode);
          }Catch(ex){
              dumpException(ex);
              i--;
          }
          TEST_VERIFY_AVL_TREE((IntNode*)root, max-i);
      }
      freeAllNodesInTree(root);
}
