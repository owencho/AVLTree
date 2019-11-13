#include "unity.h"
#include "Rotate.h"
#include "Node.h"
#include "CustomAssert.h"
Node * root;
Node node1, node2,node3, node5, node10, node15,node20,node25,node30,node35,node40,node45,node50,node55;
Node node60,node65,node70,node75,node80,node85,node90,node95,node99;
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
/*
/**
*          3                             2
*        /         rotate             /   \
*      2           ----->           1       3
*    /             RIGHT
*  1
*
**/
/*
void test_rotateRightNode(void){
    //Build number tree
    initNode(&node1,  NULL ,NULL,0);
    initNode(&node2,  &node1 ,NULL,0);
    initNode(&node3,  &node2 ,NULL,0);
    //Test
    root = rotateRightNode(&node3);
    TEST_ASSERT_EQUAL_NODE(root,node1,node3,0);
    TEST_ASSERT_EQUAL_NODE(node1,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node3,NULL,NULL,0);
    freeAllNodesInTree(root);
}
*/
/**
*             5                             3
*           /  \       rotate             /   \
*         3     6      ----->           2      5
*       /  \           RIGHT           /     /  \
*     2     4                         1     4    6
*    /
*  1
**/


void test_rotateRightComplexNode(void){
    //Build number tree
    Node * node1 = createNode(1,NULL,NULL,0);
    Node * node2 = createNode(2,node1,NULL,0);
    Node * node4 = createNode(4,NULL,NULL,0);
    Node * node6 = createNode(6,NULL,NULL,0);
    Node * node3 = createNode(3,node2,node4,0);
    Node * node5 = createNode(5,node3,node6,0);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateRightNode(node5);
    TEST_ASSERT_EQUAL_NODE(finalNode,node2,node5,0);
    TEST_ASSERT_EQUAL_NODE(node2,node1,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node5,node4,node6,0);
    TEST_ASSERT_EQUAL_NODE(node4,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node6,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node1,NULL,NULL,0);

    freeNode(node1);
    freeNode(node2);
    freeNode(node3);
    freeNode(node4);
    freeNode(node5);
    freeNode(node6);
}
///////////////////////////////////////////
/**
*         2                            5
*          \        rotate           /   \
*           5       ----->         2      7
*            \      LEFT
*             7
*
**/
void test_rotateLeftNode(void){
    //Build number tree
    Node * node7 = createNode(7,NULL,NULL,0);
    Node * node5 = createNode(5,NULL,node7,0);
    Node * node2 = createNode(2,NULL,node5,0);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateLeftNode(node2);
    TEST_ASSERT_EQUAL_NODE(finalNode,node2,node7,0);
    TEST_ASSERT_EQUAL_NODE(node2,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node7,NULL,NULL,0);
    freeNode(node2);
    freeNode(node5);
    freeNode(node7);
}
/**
*         22                            41
*        /  \        rotate           /   \
*      11   41       ----->         22    51
*          / \        LEFT         /  \     \
*        33   51                 11   33    60
*              \
*              60
**/

void test_rotateLeftComplexNode(void){
    //Build number tree
    Node * node11 = createNode(11,NULL,NULL,0);
    Node * node33 = createNode(33,NULL,NULL,0);
    Node * node60 = createNode(60,NULL,NULL,0);
    Node * node51 = createNode(51,NULL,node60,0);
    Node * node41 = createNode(41,node33,node51,0);
    Node * node22 = createNode(22,node11,node41,0);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateLeftNode(node22);
    TEST_ASSERT_EQUAL_NODE(finalNode,node22,node51,0);
    TEST_ASSERT_EQUAL_NODE(node22,node11,node33,0);
    TEST_ASSERT_EQUAL_NODE(node51,NULL,node60,0);
    TEST_ASSERT_EQUAL_NODE(node11,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node33,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node60,NULL,NULL,0);
    freeNode(node11);
    freeNode(node33);
    freeNode(node51);
    freeNode(node60);
    freeNode(node41);
    freeNode(node22);
}

///////////////////////////////////////////
/**
*         8                           8
*       /          rotate           /      Rotate        5
*     2            ----->         5        ---->       /  \
*      \            LEFT        /          RIGHT      2    8
*       5                     2
*
**/
void test_rotateLeftRightNode(void){
    //Build number tree
    Node * node5 = createNode(5,NULL,NULL,0);
    Node * node2 = createNode(2,NULL,node5,0);
    Node * node8 = createNode(8,node2,NULL,0);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateLeftRightNode(node8);
    TEST_ASSERT_EQUAL_NODE(finalNode,node2,node8,0);
    TEST_ASSERT_EQUAL_NODE(node2,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node8,NULL,NULL,0);

    freeNode(node5);
    freeNode(node2);
    freeNode(node8);
}


/**
*         10                           10                     6
*       /   \       rotate           /   \     Rotate       /  \
*      3     12     ----->         6     12     ---->      3    10
*    /  \            LEFT        /  \           RIGHT     /    /  \
*   1    6                      3   8                    1    8   12
*         \                   /
*          8                 1
**/

void test_rotateLeftRightComplexNode(void){
    //Build number tree
    Node * node12 = createNode(12,NULL,NULL,0);
    Node * node8 = createNode(8,NULL,NULL,0);
    Node * node6 = createNode(6,NULL,node8,0);
    Node * node1 = createNode(1,NULL,NULL,0);
    Node * node3 = createNode(3,node1,node6,0);
    Node * node10 = createNode(10,node3,node12,0);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateLeftRightNode(node10);
    TEST_ASSERT_EQUAL_NODE(finalNode,node3,node10,0);
    TEST_ASSERT_EQUAL_NODE(node3,node1,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node10,node8,node12,0);
    TEST_ASSERT_EQUAL_NODE(node1,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node8,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node12,NULL,NULL,0);

    freeNode(node12);
    freeNode(node8);
    freeNode(node6);
    freeNode(node1);
    freeNode(node10);
    freeNode(node3);
}

///////////////////////////////////////////
/**
*      15                    15
*       \       rotate        \         Rotate        21
*       32      ----->         21        ---->       /  \
*      /        RIGHT           \        LEFT      15    32
*     21                         32
*
**/
void test_rotateRightLeftNode(void){
    //Build number tree
    Node * node21 = createNode(21,NULL,NULL,0);
    Node * node32 = createNode(32,node21,NULL,0);
    Node * node15 = createNode(15,NULL,node32,0);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateRightLeftNode(node15);
    TEST_ASSERT_EQUAL_NODE(finalNode,node15,node32,0);
    TEST_ASSERT_EQUAL_NODE(node32,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node15,NULL,NULL,0);

    freeNode(node15);
    freeNode(node21);
    freeNode(node32);
}

/**
*         10                         10                       13
*       /   \       rotate         /   \       Rotate        /  \
*      8     16     ----->       8      13      ---->      10    16
*           /  \     RIGHT             /  \      LEFT     / \   /  \
*          13   24                    12   16            8  12 15  24
*         /  \                           /   \
*        12   15                        15    24
**/

void test_rotateRightLeftComplexNode(void){
    //Build number tree
    Node * node15 = createNode(15,NULL,NULL,0);
    Node * node12 = createNode(12,NULL,NULL,0);
    Node * node13 = createNode(13,node12,node15,0);
    Node * node24 = createNode(24,NULL,NULL,0);
    Node * node16 = createNode(16,node13,node24,0);
    Node * node8 = createNode(8,NULL,NULL,0);
    Node * node10 = createNode(10,node8,node16,0);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateRightLeftNode(node10);
    TEST_ASSERT_EQUAL_NODE(finalNode,node10,node16,0);
    TEST_ASSERT_EQUAL_NODE(node10,node8,node12,0);
    TEST_ASSERT_EQUAL_NODE(node16,node15,node24,0);
    TEST_ASSERT_EQUAL_NODE(node8,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node12,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node15,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(node24,NULL,NULL,0);

    freeNode(node15);
    freeNode(node12);
    freeNode(node13);
    freeNode(node24);
    freeNode(node16);
    freeNode(node8);
    freeNode(node10);
}
