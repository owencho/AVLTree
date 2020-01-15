#include "unity.h"
#include "Avl.h"
#include "StringCompare.h"
#include "StringNode.h"
#include "Compare.h"
#include "Balance.h"
#include "Rotate.h"
#include "Node.h"
#include "AvlError.h"
#include "Exception.h"
#include "CException.h"
#include "CustomAssert.h"
CEXCEPTION_T ex;
Node * root ;
StringNode  nodeAdd;
char* inputString;
StringNode nodeMelon,nodeMenon,nodePapaya,nodeDurian;
void setUp(void){
    nodeMelon.str ="melon";
    nodeMenon.str ="menon";
    nodePapaya.str ="papaya";
    nodeDurian.str ="durian";
}
void tearDown(void){}
void initStringNode(StringNode * node,  StringNode * left ,StringNode * right,int balanceFactor){
    node->left = left;
    node->right = right;
    node->bFactor = balanceFactor;
}
//This function is used to compare the string node inside the AVL tree
// to determine the node to be added on the left or right depends on the size
// of the string using strcmp
// stringCompare return 1 when when root  > nodeAdd
// stringCompare return -1 when when root < nodeAdd
// stringCompare return 0 when when root == nodeAdd
void test_StringCompareForAvlDelete_smaller_root_oelon_return_neg1(void){
    Compare compare = (Compare)stringCompareForAvlDelete;
    inputString = "oelon";
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&nodeMelon,(void *)inputString)));
}

void test_StringCompareForAvlDelete_same_root_melon_return_neg0(void){
    Compare compare = (Compare)stringCompareForAvlDelete;
    inputString = "melon";
    TEST_ASSERT_EQUAL(0,(compare((Node*)&nodeMelon,(void *)inputString)));
}

void test_StringCompareForAvlDelete_larger_root_papay_return_1(void){
    Compare compare = (Compare)stringCompareForAvlDelete;
    inputString = "papay";
    TEST_ASSERT_EQUAL(1,(compare((Node*)&nodePapaya,(void *)inputString)));
}

void test_StringCompareForAvlAdd_larger_root_papaqa_return_1(void){
    Compare compare = (Compare)stringCompareForAvlAdd;
    nodeAdd.str = "papaqa";
    TEST_ASSERT_EQUAL(1,(compare((Node*)&nodePapaya,(void *)&nodeAdd)));
}

void test_StringCompareForAvlAdd_smaller_root_milon_return_neg1(void){
    Compare compare = (Compare)stringCompareForAvlAdd;
    nodeAdd.str = "milon";
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&nodeMelon,(void *)&nodeAdd)));
}
void test_StringCompareForAvlAdd_same_root_return_0(void){
    Compare compare = (Compare)stringCompareForAvlAdd;
    nodeAdd.str = "durian";
    TEST_ASSERT_EQUAL(0,(compare((Node*)&nodeDurian,(void *)&nodeAdd)));
}

/**
*            melon(0)                  melon(1)
*                                         \
*                          --->           menon(0)
*                        add menon
*
*
*
**/

void test_AvlAdd_given_string(void){
    initStringNode(&nodeMenon,NULL,NULL,0);
    initStringNode(&nodeMelon,NULL,NULL,0);

    Try{
        root=avlAdd((Node*)&nodeMelon,(Node*)&nodeMenon,(Compare)stringCompareForAvlAdd);
        TEST_ASSERT_EQUAL_PTR(&nodeMelon,root);
        TEST_ASSERT_EQUAL(1,root->bFactor);
        TEST_ASSERT_EQUAL_PTR(&nodeMenon,root->right);
        TEST_ASSERT_EQUAL(0,root->right->bFactor);
        TEST_ASSERT_NULL(root->left);
        TEST_ASSERT_NULL(root->right->right);
        TEST_ASSERT_NULL(root->right->left);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
