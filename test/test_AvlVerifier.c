#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "unity.h"
#include "AvlVerifier.h"
#include "AvlAdd.h"
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

Node *createAvlNode(uint32_t value){
    Node * node =(Node * )malloc(sizeof(Node));
    node->value =value;
    node->bFactor = 1;
    node ->left = (Node*)1;
    node ->right = (Node*)1;
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

//srand(2)
//5 √ 10 √ 100 √ 1000 √ 10000 √
//time(0)
//5 √ 10 √ 100 √ 1000 √ 10000 √

//Automated Test for checking AVL add function
void test_verify_AVL_tree(void){
    Node * root;
    int max = 100000 , i;
    int height;
    srand(time(0));
    i = max;
    root =  createNode(getRandomNum(),  NULL ,NULL,0);
    while(i--){
       Try{
            root = avlAdd(root,createAvlNode(getRandomNum()));
        }Catch(ex){
            dumpException(ex);
            i++;
        }
        TEST_VERIFY_AVL_TREE(root, max-i+1);
    }
    freeAllNodesInTree(root);
}
