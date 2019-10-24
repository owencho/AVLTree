#include "unity.h"
#include "Rotate.h"
#include "Node.h"

void setUp(void){}

void tearDown(void){}

void test_rotateRightNode1(void){
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

void test_rotateLeftNode1(void){
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
