#include "unity.h"
#include "Avl.h"
#include "Node.h"
#include "CustomAssert.h"
#include "Rotate.h"

Node * root;
Node node1, node5, node10, node15,node20,node25,node30,node35,node40,node45,node50,node55;
Node node60,node65,node70,node75,node80,node85,node90,node95,node99;
void setUp(void){
    node1.value =1;   node5.value =5;   node15.value =15;
    node20.value =20; node25.value =25; node30.value =30;
    node35.value =35; node40.value =40; node45.value =45;
    node50.value =50; node55.value =55; node60.value =60;
    node65.value =65; node70.value =70; node75.value =75;
    node80.value =80; node85.value =85; node90.value =90;
    node95.value =95; node99.value =99;
}

void tearDown(void){}


/**
*            50(0)                          50(2)                               30(2)
*           /   \                           /    \           rotate             /   \
*         30(0)  60(0)   --->            30(1)    60(0)     ----->          20(-1)  50(0)
*        /  \            add  10        /    \               RIGHT           /     /     \
*     20(0)  40(0)                    20(-1)   40(0)                       10(0)    40(0)  60(0)
*                                        /
*                                     10(0)
**/


void test_AvlAdd_given_50_30_20_40_60_add_10(void){
    initNode(&node10,&node1,&node10,77);
    initNode(&node20,NULL,NULL,0);
    initNode(&node40,NULL,&node10,0);
    initNode(&node30,&node20,&node40,0);
    initNode(&node60,NULL,NULL,0);
    initNode(&node50,&node30,&node60,0);

    //Test
    root=avlAdd(&node50,&node10);
    TEST_ASSERT_EQUAL_NODE(root,&node20,&node50,2);
    TEST_ASSERT_EQUAL_NODE(&node20,&node10,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node50,&node40,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node40,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);

}

/**
*            50(1)                          50(2)                                   75(0)
*           /   \                           /    \              rotate             /     \
*         25(0)  75(0)      --->        25(0)    75(1)          ----->          50(0)     85(-1)
*                /  \      add 80                /    \         RIGHT           / \       /
*            60(0)  85(0)                    60(0)   85(-1)     LEFT        25(0)  60(0) 80(0)
*                                                    /
*                                                 80(0)
**/

void test_AvlAdd_given_50_25_75_60_85_add_80(void){
    initNode(&node80,&node1,&node10,69);
    initNode(&node85,NULL,NULL,0);
    initNode(&node60,NULL,NULL,0);
    initNode(&node75,&node60,&node85,0);
    initNode(&node25,NULL,NULL,0);
    initNode(&node50,&node25,&node75,0);

    //Test
    root=avlAdd(&node50,&node80);
    TEST_ASSERT_EQUAL_NODE(root,&node50,&node85,2);
    TEST_ASSERT_EQUAL_NODE(&node20,&node10,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node50,&node40,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node40,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);

}
