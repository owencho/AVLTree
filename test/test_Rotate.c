#include "unity.h"
#include "Rotate.h"
#include "Node.h"

void setUp(void){}

void tearDown(void){}

void test_rotateRightNode(void){
    //Build number tree
    Node * node1 = createNode(1,NULL,NULL);
    Node * node2 = createNode(2,node1,NULL);
    Node * node3 = createNode(3,node2,NULL);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateRightNode(node3);
    TEST_ASSERT_EQUAL(2,finalNode->value);
    TEST_ASSERT_EQUAL(1,finalNode->left->value);
    TEST_ASSERT_EQUAL(3,finalNode->right->value);
    TEST_ASSERT_NULL(finalNode->left->left);
    TEST_ASSERT_NULL(finalNode->left->right);
    TEST_ASSERT_NULL(finalNode->right->left);
    TEST_ASSERT_NULL(finalNode->right->right);

    freeNode(node1);
    freeNode(node2);
    freeNode(node3);
    freeNode(finalNode);
}

void test_rotateRightComplexNode(void){
    //Build number tree
    Node * node1 = createNode(1,NULL,NULL);
    Node * node2 = createNode(2,node1,NULL);
    Node * node4 = createNode(4,NULL,NULL);
    Node * node6 = createNode(6,NULL,NULL);
    Node * node3 = createNode(3,node2,node4);
    Node * node5 = createNode(5,node3,node6);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateRightNode(node5);
    TEST_ASSERT_EQUAL(3,finalNode->value);
    TEST_ASSERT_EQUAL(2,finalNode->left->value);
    TEST_ASSERT_EQUAL(5,finalNode->right->value);
    TEST_ASSERT_EQUAL(1,finalNode->left->left->value);
    TEST_ASSERT_EQUAL(6,finalNode->right->right->value);
    TEST_ASSERT_EQUAL(4,finalNode->right->left->value);
    TEST_ASSERT_NULL(finalNode->left->left->left);
    TEST_ASSERT_NULL(finalNode->left->left->right);
    TEST_ASSERT_NULL(finalNode->left->right);
    TEST_ASSERT_NULL(finalNode->right->right->left);
    TEST_ASSERT_NULL(finalNode->right->right->right);
    TEST_ASSERT_NULL(finalNode->right->left->left);
    TEST_ASSERT_NULL(finalNode->right->left->right);

    freeNode(node1);
    freeNode(node2);
    freeNode(node3);
    freeNode(node4);
    freeNode(node5);
    freeNode(node6);
    freeNode(finalNode);
}
///////////////////////////////////////////
void test_rotateLeftNode(void){
    //Build number tree
    Node * node3 = createNode(7,NULL,NULL);
    Node * node2 = createNode(5,NULL,node3);
    Node * node1 = createNode(2,NULL,node2);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateLeftNode(node1);
    TEST_ASSERT_EQUAL(5,finalNode->value);
    TEST_ASSERT_EQUAL(2,finalNode->left->value);
    TEST_ASSERT_EQUAL(7,finalNode->right->value);
    TEST_ASSERT_NULL(finalNode->left->left);
    TEST_ASSERT_NULL(finalNode->left->right);
    TEST_ASSERT_NULL(finalNode->right->left);
    TEST_ASSERT_NULL(finalNode->right->right);

    freeNode(node1);
    freeNode(node2);
    freeNode(node3);
    freeNode(finalNode);
}

void test_rotateLeftComplexNode(void){
    //Build number tree
    Node * node11 = createNode(11,NULL,NULL);
    Node * node33 = createNode(33,NULL,NULL);
    Node * node60 = createNode(60,NULL,NULL);
    Node * node51 = createNode(51,NULL,node60);
    Node * node41 = createNode(41,node33,node51);
    Node * node22 = createNode(22,node11,node41);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateLeftNode(node22);
    TEST_ASSERT_EQUAL(41,finalNode->value);
    TEST_ASSERT_EQUAL(22,finalNode->left->value);
    TEST_ASSERT_EQUAL(11,finalNode->left->left->value);
    TEST_ASSERT_EQUAL(33,finalNode->left->right->value);
    TEST_ASSERT_EQUAL(51,finalNode->right->value);
    TEST_ASSERT_EQUAL(60,finalNode->right->right->value);

    TEST_ASSERT_NULL(finalNode->left->left->left);
    TEST_ASSERT_NULL(finalNode->left->left->right);
    TEST_ASSERT_NULL(finalNode->left->right->left);
    TEST_ASSERT_NULL(finalNode->left->right->right);
    TEST_ASSERT_NULL(finalNode->right->right->left);
    TEST_ASSERT_NULL(finalNode->right->right->right);
    TEST_ASSERT_NULL(finalNode->right->left);


    freeNode(node11);
    freeNode(node33);
    freeNode(node51);
    freeNode(node60);
    freeNode(node41);
    freeNode(node22);
    freeNode(finalNode);
}

void test_rotateLeftRightNode(void){
    //Build number tree
    Node * node2 = createNode(5,NULL,NULL);
    Node * node1 = createNode(2,NULL,node2);
    Node * node3 = createNode(8,node1,NULL);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateLeftRightNode(node3);
    TEST_ASSERT_EQUAL(5,finalNode->value);
    TEST_ASSERT_EQUAL(2,finalNode->left->value);
    TEST_ASSERT_EQUAL(8,finalNode->right->value);
    TEST_ASSERT_NULL(finalNode->left->left);
    TEST_ASSERT_NULL(finalNode->left->right);
    TEST_ASSERT_NULL(finalNode->right->left);
    TEST_ASSERT_NULL(finalNode->right->right);

    freeNode(node1);
    freeNode(node2);
    freeNode(node3);
    freeNode(finalNode);
}

void test_rotateLeftRightComplexNode(void){
    //Build number tree
    Node * node12 = createNode(12,NULL,NULL);
    Node * node8 = createNode(8,NULL,NULL);
    Node * node6 = createNode(6,NULL,node8);
    Node * node1 = createNode(1,NULL,NULL);
    Node * node3 = createNode(3,node1,node6);
    Node * node10 = createNode(10,node3,node12);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateLeftRightNode(node10);
    TEST_ASSERT_EQUAL(6,finalNode->value);
    TEST_ASSERT_EQUAL(3,finalNode->left->value);
    TEST_ASSERT_EQUAL(1,finalNode->left->left->value);
    TEST_ASSERT_EQUAL(10,finalNode->right->value);
    TEST_ASSERT_EQUAL(8,finalNode->right->left->value);
    TEST_ASSERT_EQUAL(12,finalNode->right->right->value);
    TEST_ASSERT_NULL(finalNode->left->left->left);
    TEST_ASSERT_NULL(finalNode->left->left->right);
    TEST_ASSERT_NULL(finalNode->left->right);
    TEST_ASSERT_NULL(finalNode->right->left->left);
    TEST_ASSERT_NULL(finalNode->right->left->right);
    TEST_ASSERT_NULL(finalNode->right->right->left);
    TEST_ASSERT_NULL(finalNode->right->right->right);

    freeNode(node12);
    freeNode(node8);
    freeNode(node6);
    freeNode(node1);
    freeNode(node10);
    freeNode(node3);
    freeNode(finalNode);
}


void test_rotateRightLeftNode(void){
    //Build number tree
    Node * node2 = createNode(21,NULL,NULL);
    Node * node3 = createNode(32,node2,NULL);
    Node * node1 = createNode(15,NULL,node3);
    Node * finalNode = NULL;

    //Test
    finalNode=rotateRightLeftNode(node1);
    TEST_ASSERT_EQUAL(21,finalNode->value);
    TEST_ASSERT_EQUAL(15,finalNode->left->value);
    TEST_ASSERT_EQUAL(32,finalNode->right->value);
    TEST_ASSERT_NULL(finalNode->left->left);
    TEST_ASSERT_NULL(finalNode->left->right);
    TEST_ASSERT_NULL(finalNode->right->left);
    TEST_ASSERT_NULL(finalNode->right->right);

    freeNode(node1);
    freeNode(node2);
    freeNode(node3);
    freeNode(finalNode);
}
