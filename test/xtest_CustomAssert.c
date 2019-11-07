#include "unity.h"
#include "CustomAssert.h"
#include "Node.h"

Node node1, node5, node10, node15,node20,node25,node30,node35,node40,node45,node50,node55;
Node node60,node65,node70,node75,node80,node85,node90,node95,node99;
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


/**
*            50(0)
*           /   \
*         30(0)  60(0)
**/

void test_CustomAssert_given_30_50_60_expected_to_pass(void){
    initNode(&node30,NULL,NULL,0);
    initNode(&node60,NULL,NULL,0);
    initNode(&node50,&node30,&node60,0);

    //Test
    TEST_ASSERT_EQUAL_NODE(&node50,&node30,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
}


void test_CustomAssert_given_NULL_expected_to_fail(void){
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,NULL,0);
}

/**
*            60(0)
*           /   \
*         20(0)  70(0)
**/

void test_CustomAssert_given_30_20_60_expected_to_fail_on_wrong_left_node(void){
    initNode(&node70,NULL,NULL,0);
    initNode(&node20,NULL,NULL,0);
    initNode(&node60,&node20,&node70,0);

    //Test
    TEST_ASSERT_EQUAL_NODE(&node60,&node10,&node70,0);
}

/**
*            30(0)
*                \
*               70(0)
**/

void test_CustomAssert_given_30_70_expected_to_fail_on_actual_left_node_is_NULL(void){
    initNode(&node70,NULL,NULL,0);
    initNode(&node30,NULL,&node70,0);

    //Test
    TEST_ASSERT_EQUAL_NODE(&node30,&node10,&node70,0);
}

/**
*            20(0)
*           /   \
*         10(0)  30(0)
**/

void test_CustomAssert_given_30_20_10_expected_to_fail_on_expected_NULL_left_node(void){
    initNode(&node30,NULL,NULL,0);
    initNode(&node10,NULL,NULL,0);
    initNode(&node20,&node10,&node30,0);

    //Test
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,&node30,0);
}

/**
*            20(0)
*           /   \
*         10(0)  30(0)
**/
void test_CustomAssert_given_10_20_30_expected_to_fail_on_wrong_right_node(void){
    initNode(&node30,NULL,NULL,0);
    initNode(&node10,NULL,NULL,0);
    initNode(&node20,&node10,&node30,0);

    //Test
    TEST_ASSERT_EQUAL_NODE(&node20,&node10,&node40,0);
}

/**
*            60(0)
*            /
*         10(0)
**/

void test_CustomAssert_given_10_60_expected_to_fail_on_actual_right_node_is_NULL(void){
    initNode(&node10,NULL,NULL,0);
    initNode(&node60,&node10,NULL,0);

    //Test
    TEST_ASSERT_EQUAL_NODE(&node30,&node10,&node70,0);
}

/**
*            60(0)
*           /   \
*         30(0)  90(0)
**/

void test_CustomAssert_given_30_60_90_expected_to_fail_on_expected_NULL_right_node(void){
    initNode(&node30,NULL,NULL,0);
    initNode(&node90,NULL,NULL,0);
    initNode(&node60,&node30,&node90,0);

    //Test
    TEST_ASSERT_EQUAL_NODE(&node60,&node30,NULL,0);
}

void test_CustomAssert_given_30_3bfactor_expected_to_fail_on_different_expected_bfactor(void){
    initNode(&node30,NULL,NULL,1);

    //Test
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
}
