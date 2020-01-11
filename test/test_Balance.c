#include "Rotate.h"
#include "Error.h"
#include "Balance.h"
#include "Exception.h"
#include "CException.h"
#include "IntNode.h"
#include "IntCompare.h"
#include "Node.h"
#include "unity.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
Node * root;
IntNode node1, node2,node3, node5, node10, node15,node20,node25,node30,node35,node40,node45,node50,node55;
IntNode node60,node65,node70,node75,node80,node85,node90,node95,node99;
int bFactor;
void setUp(void){
    node1.value =1;   node2.value =2;  node3.value =3;
    node5.value =5;   node15.value =15;
    node20.value =20; node25.value =25; node30.value =30;
    node35.value =35; node40.value =40; node45.value =45;
    node50.value =50; node55.value =55; node60.value =60;
    node65.value =65; node70.value =70; node75.value =75;
    node80.value =80; node85.value =85; node90.value =90;
    node95.value =95; node99.value =99; node10.value =10;
}
void tearDown(void){}
void initIntNode(IntNode * node,  IntNode * left ,IntNode * right,int balanceFactor){
    node->left = left;
    node->right = right;
    node->bFactor = balanceFactor;
}
//////////////balanceForDoubleRotate//////////////////////////////////////////////////
//Left right bFactor = Root->left->right balance Factor

void test_balanceForDoubleRotate_given_root_NULL(void){
    initIntNode(&node70,NULL,NULL,0);
    initIntNode(&node60,NULL,&node70,1);
    initIntNode(&node10,NULL,NULL,0);
    initIntNode(&node30,&node10,&node60,1);
    initIntNode(&node90,NULL,NULL,0);
    initIntNode(&node80,&node30,&node90,-2);

    root=balanceForDoubleRotate(root,bFactor);
    TEST_ASSERT_NULL(root);
}
/**
*      80(-2)                             60(0)
*     /     \          Rotate           /       \
*    30(1)  90(0)      ---->         30(-1)   80(0)
*   /     \            LEFTRIGHT     /        /    \
*  10(0)  60(1)                     10(0)     70(0)  90(0)
*             \
*            70(0)
**/

void test_balanceForDoubleRotate_given_LR_80_30_10_60_90_70(void){
    initIntNode(&node70,NULL,NULL,0);
    initIntNode(&node60,NULL,&node70,1);
    initIntNode(&node10,NULL,NULL,0);
    initIntNode(&node30,&node10,&node60,1);
    initIntNode(&node90,NULL,NULL,0);
    initIntNode(&node80,&node30,&node90,-2);

    //Test
    bFactor = node80.left->right->bFactor;
    root = rotateLeftRightNode((Node*)&node80);
    root=balanceForDoubleRotate(root,bFactor);
    TEST_ASSERT_EQUAL(0,root->bFactor);
    TEST_ASSERT_EQUAL(-1,root->left->bFactor);
    TEST_ASSERT_EQUAL(0,root->right->bFactor);

}

/**
*      80(-2)                             60(0)
*     /     \          Rotate           /       \
*    30(1)  90(0)      ---->         30(0)    80(1)
*   /     \            LEFTRIGHT     /    \       \
*  10(0)  60(-1)                     10(0) 55(0)  90(0)
*           /
*        55(0)
**/

void test_balanceForDoubleRotate_given_LR_80_30_10_60_90_55(void){
    initIntNode(&node55,NULL,NULL,0);
    initIntNode(&node60,&node55,NULL,-1);
    initIntNode(&node10,NULL,NULL,0);
    initIntNode(&node30,&node10,&node60,1);
    initIntNode(&node90,NULL,NULL,0);
    initIntNode(&node80,&node30,&node90,-2);

    //Test
    bFactor = node80.left->right->bFactor;
    root = rotateLeftRightNode((Node*)&node80);
    root=balanceForDoubleRotate(root,bFactor);
    TEST_ASSERT_EQUAL(0,root->bFactor);
    TEST_ASSERT_EQUAL(0,root->left->bFactor);
    TEST_ASSERT_EQUAL(1,root->right->bFactor);

}

/**
*      60(-2)                            55(0)
*       /           rotate             /      \
*   50(1)           ----->           50(0)    60(0)
*     \           LEFT RIGHT
*    55(0)
*
**/

void test_balanceForDoubleRotate_given_LR_60_50_55(void){
    initIntNode(&node55,NULL,NULL,0);
    initIntNode(&node50,NULL,&node55,1);
    initIntNode(&node60,&node50,NULL,-2);

    //Test
    bFactor = node60.left->right->bFactor;
    root = rotateLeftRightNode((Node*)&node60);
    root=balanceForDoubleRotate(root,bFactor);
    TEST_ASSERT_EQUAL(0,root->bFactor);
    TEST_ASSERT_EQUAL(0,root->left->bFactor);
    TEST_ASSERT_EQUAL(0,root->right->bFactor);

}

/**
*            25(2)                                     30(0)
*           /   \                  rotate             /     \
*         20(0)  40(-1)           ----->         25(-1)   40(0)
*                /  \              RIGHT         /        /  \
*             30(1) 50(0)          LEFT       20(0)    35(0) 50(0)
*                \
*                 35(0)
**/

void test_balanceForDoubleRotate_given_RL_20_25_30_40_35_50(void){
    initIntNode(&node35,NULL,NULL,0);
    initIntNode(&node30,NULL,&node35,1);
    initIntNode(&node50,NULL,NULL,0);
    initIntNode(&node40,&node30,&node50,-1);
    initIntNode(&node20,NULL,NULL,0);
    initIntNode(&node25,&node20,&node40,2);

    //Test
    bFactor = node25.right->left->bFactor;
    root = rotateRightLeftNode((Node*)&node25);
    root = balanceForDoubleRotate(root,bFactor);
    TEST_ASSERT_EQUAL(0,root->bFactor);
    TEST_ASSERT_EQUAL(-1,root->left->bFactor);
    TEST_ASSERT_EQUAL(0,root->right->bFactor);

}

/**
*            25(2)                                     35(0)
*           /   \                  rotate             /     \
*         20(0)  40(-1)           ----->         25(0)     40(1)
*                /  \              RIGHT         /   \        \
*             35(-1) 50(0)          LEFT       20(0) 30(0)   50(0)
*               /
*             30(0)
**/

void test_balanceForDoubleRotate_given_RL_bf1_20_25_30_40_35_50(void){
    initIntNode(&node30,NULL,NULL,0);
    initIntNode(&node35,&node30,NULL,-1);
    initIntNode(&node50,NULL,NULL,0);
    initIntNode(&node40,&node35,&node50,-1);
    initIntNode(&node20,NULL,NULL,0);
    initIntNode(&node25,&node20,&node40,2);

    //Test
    bFactor = node25.right->left->bFactor;
    root = rotateRightLeftNode((Node*)&node25);
    root = balanceForDoubleRotate(root,bFactor);
    TEST_ASSERT_EQUAL(0,root->bFactor);
    TEST_ASSERT_EQUAL(0,root->left->bFactor);
    TEST_ASSERT_EQUAL(1,root->right->bFactor);

}

/**
*    50(2)                               55(0)
*       \           rotate             /      \
*     60(-1)         ----->         50(0)    60(0)
*     /           RIGHT LEFT
*    55(0)
*
**/

void test_balanceForDoubleRotate_given_RL_50_55_60(void){
    initIntNode(&node55,NULL,NULL,0);
    initIntNode(&node60,&node55,NULL,-1);
    initIntNode(&node50,NULL,&node60,2);

    //Test
    bFactor = node50.right->left->bFactor;
    root = rotateRightLeftNode((Node*)&node50);
    root = balanceForDoubleRotate(root,bFactor);
    TEST_ASSERT_EQUAL(0,root->bFactor);
    TEST_ASSERT_EQUAL(0,root->left->bFactor);
    TEST_ASSERT_EQUAL(0,root->right->bFactor);

}
