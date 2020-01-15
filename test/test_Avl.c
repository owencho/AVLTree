#include "unity.h"
#include "Avl.h"
#include "Node.h"
#include "IntNode.h"
#include "IntCompare.h"
#include "Balance.h"
#include "CustomAssert.h"
#include "mock_ProcessorTest.h"
#include "Rotate.h"
#include "Exception.h"
#include "AvlError.h"
#include "CException.h"

CEXCEPTION_T ex;
Node * root;
int heightInc;
IntNode node1, node5, node10, node15,node20,node25,node30,node35,node40,node45,node50,node55;
IntNode node60,node65,node70,node75,node80,node85,node90,node95,node99;
void setUp(void){
    node1.value =1;   node5.value =5;   node15.value =15;
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

////////////////////////////////////////////////////////////////////////////////
///findSmallestNode/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//This function is used to find the smallestNode inside the root tree
/**
*    10(2)
*       \
*     30(0)
*    /    \
*  20(0)  35(0)
*
**/

void test_findSmallestNode_10_30_20_35(void){
    initIntNode(&node20,NULL,NULL,0);
    initIntNode(&node35,NULL,NULL,0);
    initIntNode(&node30,&node20,&node35,0);
    initIntNode(&node10,NULL,&node30,2);
    Try{
        root=findSmallestNode((Node*)&node10);
        TEST_ASSERT_EQUAL_PTR(&node10,root);
    }Catch(ex){
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/**
*       40(1)
*       /    \
*     30(0)  50(0)
*           /    \
*         45(0)  55(0)
*
**/

void test_findSmallestNode_40_50_30_45_55(void){
    initIntNode(&node45,NULL,NULL,0);
    initIntNode(&node30,NULL,NULL,0);
    initIntNode(&node55,NULL,NULL,0);
    initIntNode(&node50,&node45,&node55,0);
    initIntNode(&node40,&node30,&node50,1);
    Try{
        root=findSmallestNode((Node*)&node40);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

void test_findSmallestNode_root_NULL(void){
    Try{
        root=findSmallestNode(NULL);
        TEST_ASSERT_NULL(root);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
////////////////////////////////////////////////////////////////////////////////
///visitPostOrder/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//This function is used to visit all node by post order
// this function requires AVLProcessor which user need to include their function
// to actually let this function traverse node and execute the function that user passed in
/**
*    10(2)
*       \
*     30(0)
*    /    \
*  20(0)  35(0)
*
**/

void test_visitPostOrder_20_30_35_10(void){
    initIntNode(&node20,NULL,NULL,0);
    initIntNode(&node35,NULL,NULL,0);
    initIntNode(&node30,&node20,&node35,0);
    initIntNode(&node10,NULL,&node30,2);

    freeAllNodesInTree_Expect((Node*)&node20);
    freeAllNodesInTree_Expect((Node*)&node35);
    freeAllNodesInTree_Expect((Node*)&node30);
    freeAllNodesInTree_Expect((Node*)&node10);
    visitPostOrder((Node*)&node10,(AVLProcessor)freeAllNodesInTree);
}

void test_visitPostOrder_expect_no_execution_as_input_NULL(void){
    initIntNode(&node20,NULL,NULL,0);
    initIntNode(&node35,NULL,NULL,0);
    initIntNode(&node30,&node20,&node35,0);
    initIntNode(&node10,NULL,&node30,2);

    visitPostOrder(NULL,(AVLProcessor)freeAllNodesInTree);
}

void test_visitPostOrder_expect_no_execution_as_processor_NULL(void){
    initIntNode(&node20,NULL,NULL,0);
    initIntNode(&node35,NULL,NULL,0);
    initIntNode(&node30,&node20,&node35,0);
    initIntNode(&node10,NULL,&node30,2);

    visitPostOrder((Node*)&node10,NULL);
}
