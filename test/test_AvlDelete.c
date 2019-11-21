#include "unity.h"
#include "AvlAdd.h"
#include "AvlDelete.h"
#include "Node.h"
#include "CustomAssert.h"
#include "Rotate.h"
#include "Exception.h"
#include "Error.h"
#include "CException.h"

CEXCEPTION_T ex;
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
    node95.value =95; node99.value =99; node10.value =10;
}

//////////////Avl Delete without same Root inside Rotate//////////////////////////////////////////////////


//////////////Avl Delete without Rotate//////////////////////////////////////////////////
/**
*             80(-1)                               80(-1)
*           /       \                              /     \
*         40(0)     90(1)         --->          40(1)    90(1)
*        /    \         \        remove  1     /    \       \
*      10(-1)  60(0)  99(0)                10(0)   60(0)   99(0)
*        /       /  \                              /   \
*      1(0)   50(0) 70(0)                       50(0) 70(0)
**/

void test_AvlDelete_given_WO_5_30_20_25_35_40_45_50_1_delete_1(void){
    initNode(&node1,NULL,NULL,0);
    initNode(&node99,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node70,NULL,NULL,0);
    initNode(&node60,&node50,&node70,0);
    initNode(&node10,&node1,NULL,-1);
    initNode(&node40,&node10,&node60,0);
    initNode(&node90,NULL,&node99,1);
    initNode(&node80,&node40,&node90,-1);

    //Test
//    root=avlDelete(&node80,1);
    TEST_ASSERT_EQUAL_PTR(&node80,root);
    TEST_ASSERT_EQUAL_NODE(root,&node40,&node90,-1);
    TEST_ASSERT_EQUAL_NODE(&node40,&node10,&node60,1);
    TEST_ASSERT_EQUAL_NODE(&node60,&node50,&node70,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node90,NULL,&node99,1);
    TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node99,NULL,NULL,0);
}
//////////////Avl Delete with LEFT Rotation//////////////////////////////////////////////////
/**
*       10(1)                   10(2)                             25(0)
*       /  \         delete        \           rotate             /   \
*     5(0) 25(1)     ---->        25(1)         ----->         10(0)  35(0)
*            \         5             \           LEFT
*             35(0)                 35(0)
*
**/

void test_AvlDelete_given_L_5_10_25_35_delete_5(void){
    //Build number tree
    initNode(&node5,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node25,NULL,&node35,1);
    initNode(&node10,&node5,&node25,1);

    //Test
  //  root=avlDelete(&node10,5);
    TEST_ASSERT_EQUAL_PTR(&node25,root);
    TEST_ASSERT_EQUAL_NODE(root,&node10,&node35,0);
    TEST_ASSERT_EQUAL_NODE(&node35,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);

}

/**
*       30(1)                     30(2)                                70(-1)
*       /   \         delete        \              rotate             /   \
*     5(0)  70(0)     ---->        70(0)            ----->         30(1)  75(0)
*          /   \         5         /    \           LEFT              \
*        65(0) 75(0)              65(0) 75(0)                         65(0)
*
**/

void test_AvlDelete_given_L_5_30_70_65_75_delete_5(void){
    //Build number tree
    initNode(&node5,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node25,NULL,&node35,1);
    initNode(&node30,NULL,&node70,1);

    //Test
  //  root=avlDelete(&node30,5);
    TEST_ASSERT_EQUAL_PTR(&node70,root);
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node75,-1);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,&node65,1);
    TEST_ASSERT_EQUAL_NODE(&node65,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node75,NULL,NULL,0);

}
