#include "unity.h"
#include "AvlAdd.h"
#include "IntCompare.h"
#include "IntNode.h"
#include "Compare.h"
#include "Balance.h"
#include "Rotate.h"
#include "Node.h"
#include "Error.h"
#include "Exception.h"
#include "CException.h"
#include "CustomAssert.h"
CEXCEPTION_T ex;
Node * root ;
IntNode nodeAdd;
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
// IntCompare return 1 when when root > nodeAdd
// IntCompare return -1 when when root < nodeAdd
// IntCompare return 0 when when root == nodeAdd
void test_IntCompareForAvlDelete_smaller_root_return_neg1(void){
    Compare compare = (Compare)intCompareForAvlDelete;
    int i = 56;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&node5,(void *)&i)));
}

void test_IntCompareForAvlDelete_larger_root_return_1(void){
    Compare compare = (Compare)intCompareForAvlDelete;
    int i = 4;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&node5,(void *)&i)));
}

void test_IntCompareForAvlDelete_equal_root_return_0(void){
    Compare compare = (Compare)intCompareForAvlDelete;
    int i = 5;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&node5,(void *)&i)));
}

void test_IntCompareForAvlAdd_smaller_root_return_neg1(void){
    Compare compare = (Compare)intCompareForAvlAdd;
    nodeAdd.value = 56;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&node5,(void *)&nodeAdd)));
}

void test_IntCompareForAvlAdd_larger_root_return_1(void){
    Compare compare = (Compare)intCompareForAvlAdd;
    nodeAdd.value = 4;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&node5,(void *)&nodeAdd)));
}

void test_IntCompareForAvlAdd_equal_root_return_0(void){
    Compare compare = (Compare)intCompareForAvlAdd;
    nodeAdd.value =5;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&node5,(void *)&nodeAdd)));
}

/**
*            40(-1)                               40(-1)
*           /     \                              /     \
*         20(1)    45(1)        --->          20(0)    45(1)
*        /  \        \        add  1         /    \       \
*     5(0)  30(0)    50(0)                5(-1)   30(0)   50(0)
*           /  \                         /        /   \
*         25(0) 35(0)                  1(0)     25(0) 35(0)
**/

void test_AvlAdd_given_WO_5_30_20_25_35_40_45_50_add_1(void){
    initIntNode(&node1,&node10,&node10,77);
    initIntNode(&node50,NULL,NULL,0);
    initIntNode(&node25,NULL,NULL,0);
    initIntNode(&node35,NULL,NULL,0);
    initIntNode(&node30,&node25,&node35,0);
    initIntNode(&node5,NULL,NULL,0);
    initIntNode(&node20,&node5,&node30,1);
    initIntNode(&node45,NULL,&node50,1);
    initIntNode(&node40,&node20,&node45,-1);

    Try{
        root=avlAdd((Node*)&node40,(Node*)&node1,(Compare)intCompareForAvlAdd);
        TEST_ASSERT_EQUAL_PTR(&node40,root);
        TEST_ASSERT_EQUAL_INT_NODE((IntNode*)root,&node20,&node45,-1);
        TEST_ASSERT_EQUAL_INT_NODE(&node20,&node5,&node30,0);
        TEST_ASSERT_EQUAL_INT_NODE(&node30,&node25,&node35,0);
        TEST_ASSERT_EQUAL_INT_NODE(&node5,&node1,NULL,-1);
        TEST_ASSERT_EQUAL_INT_NODE(&node45,NULL,&node50,1);
        TEST_ASSERT_EQUAL_INT_NODE(&node25,NULL,NULL,0);
        TEST_ASSERT_EQUAL_INT_NODE(&node35,NULL,NULL,0);
        TEST_ASSERT_EQUAL_INT_NODE(&node50,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
