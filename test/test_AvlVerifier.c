#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "unity.h"
#include "AvlVerifier.h"
#include "Avl.h"
#include "Node.h"
#include "CException.h"
#include "CustomAssert.h"
#include "Rotate.h"
#include "Exception.h"

CEXCEPTION_T ex;
void setUp(void){}
void tearDown(void){}

Node *createAvlNode(uint32_t value){
    Node * node =(Node * )malloc(sizeof(Node));
    node->value =value;
    node->bFactor = 1;
    node ->left = (Node*)1;
    node ->right = (Node*)1;
}

void freeAllNodesInTree(Node *root){
      if(root->left != NULL){
          freeAllNodesInTree(root->left);
      }
      if (root->right != NULL){
          freeAllNodesInTree(root->right);
      }
      freeNode(root);
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


void test_verify_AVL_tree(void){
    Node * root;
    int max = 1000 , i;
    int height;
    srand(1234);
    i = max;
    root =  createNode(getRandomNum(),  NULL ,NULL,0);
    while(i--){
       Try{
            root = avlAdd(root,createAvlNode(getRandomNum()));
        }Catch(ex){
            printf("Exception Thrown");
            i++;
        }
        TEST_VERIFY_AVL_TREE(root, max-i);
    }
    freeAllNodesInTree(root);
}
