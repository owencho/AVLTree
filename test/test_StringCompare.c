#include "unity.h"
#include "AvlAdd.h"
#include "StringCompare.h"
#include "StringNode.h"
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
StringNode nodeMelon,nodeMenon,nodePapaya,nodeDurian;
void setUp(void){
    nodeMelon.value ="melon";
    nodeMenon.value ="menon";
    nodePapaya.value ="papaya";
    nodeDurian.value ="durian";
}
void tearDown(void){}
void initStringNode(StringNode * node,  StringNode * left ,StringNode * right,int balanceFactor){
    node->left = left;
    node->right = right;
    node->bFactor = balanceFactor;
}
// stringCompare return 1 when when root > nodeAdd
// stringCompare return -1 when when root < nodeAdd
// stringCompare return 0 when when root == nodeAdd
void test_StringCompare_smaller_root_oelon_return_neg1(void){
    Compare compare = (Compare)stringCompare;
    char* i = "oelon";
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&nodeMelon,(void *)i)));
}

void test_StringCompare_smaller_root_milon_return_neg1(void){
    Compare compare = (Compare)stringCompare;
    char* i = "milon";
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&nodeMelon,(void *)i)));
}

void test_StringCompare_smaller_root_meeon_return_neg1(void){
    Compare compare = (Compare)stringCompare;
    char* i = "menon";
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&nodeMelon,(void *)i)));
}

void test_StringCompare_larger_root_papay_return_1(void){
    Compare compare = (Compare)stringCompare;
    char* i = "papay";
    TEST_ASSERT_EQUAL(1,(compare((Node*)&nodePapaya,(void *)i)));
}

void test_StringCompare_larger_root_papaqa_return_1(void){
    Compare compare = (Compare)stringCompare;
    char* i = "papaqa";
    TEST_ASSERT_EQUAL(1,(compare((Node*)&nodePapaya,(void *)i)));
}

void test_StringCompare_same_root_return_0(void){
    Compare compare = (Compare)stringCompare;
    char* i = "durian";
    TEST_ASSERT_EQUAL(0,(compare((Node*)&nodeDurian,(void *)i)));
}

/**
*            melon(0)                     melon(-1)
*                                         /
*                          --->         menon(0)
*                        add menon
*
*
*
**/

void test_AvlAdd_given_string(void){
    initStringNode(&nodeMenon,NULL,NULL,0);
    initStringNode(&nodeMelon,NULL,NULL,0);

    Try{
        root=avlAdd((Node*)&nodeMelon,(Node*)&nodeMenon,(Compare)stringCompare);
        TEST_ASSERT_EQUAL_PTR(&nodeMelon,root);
        TEST_ASSERT_EQUAL(-1,root->bFactor);
        TEST_ASSERT_EQUAL_PTR(&nodeMenon,root->left);
        TEST_ASSERT_EQUAL(0,root->left->bFactor);
        TEST_ASSERT_NULL(root->right);
        TEST_ASSERT_NULL(root->left->right);
        TEST_ASSERT_NULL(root->left->left);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
