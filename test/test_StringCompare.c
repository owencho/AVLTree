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
StringNode nodeMelon,nodePapaya,nodeDurian;
void setUp(void){
    nodeMelon.value ="melon";
    nodePapaya.value ="papaya";
    nodeDurian.value ="durian";
}
void tearDown(void){}
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
