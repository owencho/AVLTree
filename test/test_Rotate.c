#include "unity.h"
#include "Rotate.h"
#include "Node.h"
#include "CustomAssert.h"
#include "Exception.h"
#include "Error.h"
#include "CException.h"
#include "IntNode.h"
#include "IntCompare.h"

Node * root;
IntNode node1, node2,node3, node5, node10, node15,node20,node25,node30,node35,node40,node45,node50,node55;
IntNode node60,node65,node70,node75,node80,node85,node90,node95,node99;
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
////Rotate Right///
/**
*          30                           20
*        /         rotate             /   \
*      20          ----->           10     30
*    /             RIGHT
*  10
*
**/

void test_rotateRightNode(void){
    initIntNode(&node10,  NULL ,NULL,0);
    initIntNode(&node20,  &node10 ,NULL,0);
    initIntNode(&node30,  &node20 ,NULL,0);

    root = rotateRightNode((Node*)&node30);
    TEST_ASSERT_EQUAL(root,&node20);
    TEST_ASSERT_EQUAL_INT_NODE((IntNode*)root,&node10,&node30,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node10,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node30,NULL,NULL,0);
}

/**
*             50                              30
*           /  \         rotate             /   \
*         30     60      ----->           20     50
*       /  \            RIGHT           /      /   \
*     20     40                       10     40    60
*    /
*  10
**/


void test_rotateRightComplexNode(void){
    initIntNode(&node10,  NULL ,NULL,0);
    initIntNode(&node40,  NULL ,NULL,0);
    initIntNode(&node60,  NULL ,NULL,0);
    initIntNode(&node20,  &node10 ,NULL,0);
    initIntNode(&node30,  &node20 ,&node40,0);
    initIntNode(&node50,  &node30 ,&node60,0);

    root=rotateRightNode((Node*)&node50);
    TEST_ASSERT_EQUAL(root,&node30);
    TEST_ASSERT_EQUAL_INT_NODE((IntNode*)root,&node20,&node50,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node20,&node10,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node50,&node40,&node60,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node40,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node60,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node10,NULL,NULL,0);
}
///////////////////////////Rotate Left///////////////////////
/**
*         20                           50
*          \        rotate           /   \
*           50       ----->         20    70
*            \      LEFT
*             70
*
**/
void test_rotateLeftNode(void){
    initIntNode(&node70,  NULL ,NULL,0);
    initIntNode(&node50,  NULL,&node70,0);
    initIntNode(&node20,  NULL ,&node50,0);

    root=rotateLeftNode((Node*)&node20);
    TEST_ASSERT_EQUAL(root,&node50);
    TEST_ASSERT_EQUAL_INT_NODE((IntNode*)root,&node20,&node70,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node70,NULL,NULL,0);
}
/**
*         20                            40
*        /  \        rotate           /   \
*      10   40       ----->         20    50
*          / \        LEFT         /  \     \
*        30   50                 10   30    60
*              \
*              60
**/

void test_rotateLeftComplexNode(void){
    initIntNode(&node10,  NULL ,NULL,0);
    initIntNode(&node30,  NULL ,NULL,0);
    initIntNode(&node60,  NULL ,NULL,0);
    initIntNode(&node50, NULL, &node60 ,0);
    initIntNode(&node40,  &node30 ,&node50,0);
    initIntNode(&node20,  &node10 ,&node40,0);

    root=rotateLeftNode((Node*)&node20);
    TEST_ASSERT_EQUAL(root,&node40);
    TEST_ASSERT_EQUAL_INT_NODE((IntNode*)root,&node20,&node50,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node20,&node10,&node30,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node50,NULL,&node60,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node10,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node30,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node60,NULL,NULL,0);
}
///////////////////////////Rotate Left Right///////////////////////
/**
*         80                         80
*       /          rotate           /      Rotate        50
*     20            ----->        50       ---->       /  \
*      \            LEFT        /          RIGHT     20    80
*       50                     20
*
**/
void test_rotateLeftRightNode(void){
    initIntNode(&node50,  NULL ,NULL,0);
    initIntNode(&node20, NULL, &node50,0);
    initIntNode(&node80,  &node20 ,NULL,0);

    root=rotateLeftRightNode((Node*)&node80);
    TEST_ASSERT_EQUAL(root,&node50);
    TEST_ASSERT_EQUAL_INT_NODE((IntNode*)root,&node20,&node80,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node80,NULL,NULL,0);
}


/**
*         90                          90                     60
*       /   \       rotate           /   \     Rotate       /  \
*      30     99    ----->         60     99     ---->    30    90
*    /  \            LEFT        /  \           RIGHT     /    /  \
*  10    60                     30    80                 10   80   99
*         \                   /
*          80                10
**/

void test_rotateLeftRightComplexNode(void){
    initIntNode(&node10,  NULL ,NULL,0);
    initIntNode(&node80,  NULL ,NULL,0);
    initIntNode(&node99,  NULL ,NULL,0);
    initIntNode(&node60, NULL, &node80 ,0);
    initIntNode(&node30,  &node10 ,&node60,0);
    initIntNode(&node90,  &node30 ,&node99,0);

    root=rotateLeftRightNode((Node*)&node90);
    TEST_ASSERT_EQUAL(root,&node60);
    TEST_ASSERT_EQUAL_INT_NODE((IntNode*)root,&node30,&node90,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node30,&node10,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node90,&node80,&node99,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node10,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node80,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node99,NULL,NULL,0);
}

///////////////////////////Rotate Right Left///////////////////////
/**
*      10                    10
*       \       rotate        \         Rotate        20
*       30      ----->         20        ---->       /  \
*      /        RIGHT           \        LEFT      10    30
*     20                         30
*
**/
void test_rotateRightLeftNode(void){
    initIntNode(&node20,  NULL ,NULL,0);
    initIntNode(&node30,  &node20 ,NULL,0);
    initIntNode(&node10, NULL, &node30 ,0);

    root=rotateRightLeftNode((Node*)&node10);
    TEST_ASSERT_EQUAL(root,&node20);
    TEST_ASSERT_EQUAL_INT_NODE((IntNode*)root,&node10,&node30,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node30,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node10,NULL,NULL,0);
}

/**
*         20                         20                       30
*       /   \       rotate         /   \       Rotate        /  \
*      10    40     ----->       10     30      ---->      20    40
*           /  \     RIGHT             /  \      LEFT     / \   /  \
*          30   45                    25   40            10  25 35  45
*         /  \                           /   \
*        25   35                        35    45
**/

void test_rotateRightLeftComplexNode(void){
    initIntNode(&node45,  NULL ,NULL,0);
    initIntNode(&node35,  NULL ,NULL,0);
    initIntNode(&node25,  NULL ,NULL,0);
    initIntNode(&node10, NULL, NULL ,0);
    initIntNode(&node30,  &node25 ,&node35,0);
    initIntNode(&node40,  &node30 ,&node45,0);
    initIntNode(&node20,  &node10 ,&node40,0);

    root=rotateRightLeftNode((Node*)&node20);
    TEST_ASSERT_EQUAL(root,&node30);
    TEST_ASSERT_EQUAL_INT_NODE((IntNode*)root,&node20,&node40,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node20,&node10,&node25,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node40,&node35,&node45,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node10,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node25,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node35,NULL,NULL,0);
    TEST_ASSERT_EQUAL_INT_NODE(&node45,NULL,NULL,0);
}
