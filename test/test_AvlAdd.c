#include "unity.h"
#include "Avl.h"
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

void tearDown(void){}


/**
*            50(-1)                          50(-2)                             30(0)
*           /   \                           /    \           rotate             /   \
*         30(0)  60(0)   --->            30(-1)    60(0)     ----->          20(-1)  50(0)
*        /  \            add  10        /    \               RIGHT           /     /     \
*     20(0)  40(0)                    20(-1)   40(0)                       10(0)  40(0)  60(0)
*                                     /
*                                   10(0)
**/

void test_AvlAdd_given_50_30_20_40_60_add_10(void){
    initNode(&node10,&node1,&node10,77);
    initNode(&node20,NULL,NULL,0);
    initNode(&node40,NULL,NULL,0);
    initNode(&node30,&node20,&node40,0);
    initNode(&node60,NULL,NULL,0);
    initNode(&node50,&node30,&node60,-1);

    //Test
    root=avlAdd(&node50,&node10);
    TEST_ASSERT_EQUAL_NODE(root,&node20,&node50,0);
    TEST_ASSERT_EQUAL_NODE(&node20,&node10,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node50,&node40,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node40,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
}

/**
*            5(1)                            5(2)                                5(1)
*           /   \                          /    \            rotate             /   \
*         1(0)  60(-1)         --->     1(0)   60(-2)        ----->          1(0)  50(0)
*              /              add  40           /             RIGHT              /     \
*           50(0)                             50(-1)                           40(0)  60(0)
*                                             /
*                                           40(0)
**/

void test_AvlAdd_given_5_1_60_50_add_40(void){
    initNode(&node40,&node20,&node10,77);
    initNode(&node1,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node60,&node50,NULL,-1);
    initNode(&node5,&node1,&node60,1);

    //Test
    root=avlAdd(&node5,&node40);
    TEST_ASSERT_EQUAL_NODE(root,&node1,&node50,1);
    TEST_ASSERT_EQUAL_NODE(&node50,&node40,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node40,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node1,NULL,NULL,0);
}

/**
*         80(-1)                      80(-2)                             60(0)
*       /      \         add          /     \         Rotate          /       \
*    30(0)    90(0)     ----->     30(1)  90(0)      ---->         30(-1)   80(0)
*    /  \              70         /     \             LEFTRIGHT     /        /    \
*  10(0) 60(0)                  10(0)  60(1)                     10(0)     70(0)  90(0)
*                                        \
*                                        70(0)
**/

void test_AvlAdd_given_80_30_10_60_90_add_70(void){
    initNode(&node70,&node1,&node10,77);
    initNode(&node60,NULL,NULL,0);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,0);
    initNode(&node90,NULL,NULL,0);
    initNode(&node80,&node30,&node90,-1);

    //Test
    root=avlAdd(&node80,&node70);
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node80,0);
    TEST_ASSERT_EQUAL_NODE(&node30,&node10,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node80,&node70,&node90,0);
    TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node90,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
}

/**
*            50(1)                          50(3)                                   75(0)
*           /   \                           /    \              rotate             /     \
*         25(0)  75(0)      --->        25(0)    75(2)          ----->          50(0)     85(-1)
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
    initNode(&node50,&node25,&node75,1);

    //Test
    root=avlAdd(&node50,&node80);
    TEST_ASSERT_EQUAL_NODE(root,&node50,&node85,0);
    TEST_ASSERT_EQUAL_NODE(&node50,&node25,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node85,&node80,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node25,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node80,NULL,NULL,0);

}

/**
*            25(1)                      25(2)                           40(0)
*           /  \                        /  \           rotate           /   \
*         10(0) 40(0)    ------>    10(0)   40(1)       ----->       25(0)    50(1)
*              /  \       add 60           /  \          LEFT         /  \     \
*            30(0) 50(0)                30(0) 50(1)                10(0) 30(0) 60(0)
*                                              \
*                                             60(0)
**/

void test_AvlAdd_given_25_10_40_30_50_add_60(void){
    //Build number tree
    initNode(&node60,&node1,&node10,69);
    initNode(&node50,NULL,NULL,0);
    initNode(&node30,NULL,NULL,0);
    initNode(&node40,&node30,&node50,0);
    initNode(&node10,NULL,NULL,0);
    initNode(&node25,&node10,&node40,1);

    //Test
    root=avlAdd(&node25,&node60);
    TEST_ASSERT_EQUAL_NODE(root,&node25,&node50,0);
    TEST_ASSERT_EQUAL_NODE(&node25,&node10,&node30,0);
    TEST_ASSERT_EQUAL_NODE(&node50,NULL,&node60,1);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
}
    /**
    *          30(-2)                            20(0)
    *        /              rotate             /      \
    *      20(-1)           ----->           10(0)    30(0)
    *    /                  RIGHT
    *  10(0)
    *
    **/

void test_rotateRightAndReBalance_given_30_20_10(void){
    initNode(&node10,NULL,NULL,0);
    initNode(&node20,&node10,NULL,-1);
    initNode(&node30,&node20,NULL,-2);

    //Test
    root=rotateRightAndReBalance(&node30);
    TEST_ASSERT_EQUAL_NODE(root,&node10,&node30,0);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);

}

/**
*            60(-2)                            40(0)
*           /   \          rotate             /   \
*         40(-1)  70(0)   ----->          30(-1)  60(0)
*        /  \             RIGHT           /     /     \
*     30(-1)  50(0)      rebalance       20(0)  50(0)  70(0)
*      /
*  20(0)
**/

void test_rotateRightAndReBalance_given_50_30_20_40_60_10(void){
    initNode(&node20,NULL,NULL,0);
    initNode(&node30,&node20,NULL,-1);
    initNode(&node50,NULL,NULL,0);
    initNode(&node40,&node30,&node50,-1);
    initNode(&node70,NULL,NULL,0);
    initNode(&node60,&node40,&node70,-2);

    //Test
    root=rotateRightAndReBalance(&node60);
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node30,&node20,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node60,&node50,&node70,0);
    TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);

}

/**
*        80(-2)                            60(0)
*       /     \          Rotate          /       \
*    30(1)  90(0)        ---->         30(-1)   80(0)
*   /     \             LEFTRIGHT     /        /    \
* 10(0)   60(1)        rebalance   10(0)     70(0)  90(0)
*            \
*            70(0)
**/

void test_rotateRightAndReBalance_given_80_30_10_60_90_70(void){
    initNode(&node70,NULL,NULL,0);
    initNode(&node60,NULL,&node70,1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,0);
    initNode(&node90,NULL,NULL,0);
    initNode(&node80,&node30,&node90,-2);

    //Test
    root=rotateRightAndReBalance(&node80);
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node80,0);
    TEST_ASSERT_EQUAL_NODE(&node30,&node10,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node80,&node70,&node90,0);
    TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node90,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
}
/**
*              35(2)                           50(0)
*              /  \           rotate           /   \
*         20(0)   50(1)       ----->       35(0)    60(1)
*                /  \          LEFT         /  \     \
*            40(0) 60(1)     rebalance   20(0) 40(0) 70(0)
*                      \
*                     70(0)
**/

void test_rotateLeftAndReBalance_given_25_10_40_30_50_add_60(void){
    //Build number tree
    initNode(&node70,NULL,NULL,0);
    initNode(&node60,NULL,&node70,1);
    initNode(&node40,NULL,NULL,0);
    initNode(&node50,&node40,&node60,1);
    initNode(&node20,NULL,NULL,0);
    initNode(&node35,&node20,&node50,2);

    //Test
    root=rotateLeftAndReBalance(&node35);
    TEST_ASSERT_EQUAL_NODE(root,&node35,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node35,&node20,&node40,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,&node70,1);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node40,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);

}

/**
*            50(3)                                   75(0)
*           /    \              rotate             /     \
*       25(0)    75(1)          ----->          50(0)     85(-1)
*                /    \         RIGHT           / \       /
*             60(0)   85(-1)    LEFT      25(0)  60(0) 80(0)
*                      /       rebalance
*                    80(0)
**/

void test_rotateLeftAndReBalance_given_50_25_75_60_85_80(void){
    initNode(&node85,&node80,NULL,-1);
    initNode(&node80,NULL,NULL,0);
    initNode(&node60,NULL,NULL,0);
    initNode(&node75,&node60,&node85,1);
    initNode(&node25,NULL,NULL,0);
    initNode(&node50,&node25,&node75,3);

    //Test
    root=rotateLeftAndReBalance(&node50);
    TEST_ASSERT_EQUAL_NODE(root,&node50,&node85,0);
    TEST_ASSERT_EQUAL_NODE(&node50,&node25,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node85,&node80,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node25,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node80,NULL,NULL,0);

}

/**
*                 25(2)                            40(0)
*                 /  \            rotate            /   \
*             10(0)   40(1)       ----->        25(0)   50(1)
*                     /  \         LEFT          /  \     \
*                  30(0) 50(1)    rebalance    10(0) 30(0) 60(0)
*                           \
*                           60(0)
**/

void test_rotateLeftAndRebalance_given_25_10_40_30_50_add_60(void){
    //Build number tree
    initNode(&node60,NULL,NULL,0);
    initNode(&node50,NULL,&node60,1);
    initNode(&node30,NULL,NULL,0);
    initNode(&node40,&node30,&node50,1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node25,&node10,&node40,2);

    //Test
    root=rotateLeftAndReBalance(&node25);
    TEST_ASSERT_EQUAL_NODE(root,&node25,&node50,0);
    TEST_ASSERT_EQUAL_NODE(&node25,&node10,&node30,0);
    TEST_ASSERT_EQUAL_NODE(&node50,NULL,&node60,1);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);

}

/**
*         20(2)                           50(0)
*          \           rotate             /   \
*           50(1)       ----->         20(0)  70(0)
*            \           LEFT
*             70(0)      rebalance
*
**/

void test_rotateLeftAndRebalance_given_20_50_70(void){
    //Build number tree
    initNode(&node60,NULL,NULL,0);
    initNode(&node50,NULL,&node60,1);
    initNode(&node30,NULL,NULL,0);
    initNode(&node40,&node30,&node50,1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node25,&node10,&node40,2);

    //Test
    root=rotateLeftAndReBalance(&node25);
    TEST_ASSERT_EQUAL_NODE(root,&node25,&node50,0);
    TEST_ASSERT_EQUAL_NODE(&node25,&node10,&node30,0);
    TEST_ASSERT_EQUAL_NODE(&node50,NULL,&node60,1);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);

}

/**
*                 50(1)                              50(0)
*                /   \               --->           /   \
*              20(2)  70(0)       rebalance      20(0)  70(0)
*
**/

void test_reBalanceFactor_given_20_50_70(void){
    //Build number tree
    initNode(&node70,NULL,NULL,0);
    initNode(&node20,NULL,NULL,2);
    initNode(&node50,&node20,&node70,1);

    //Test
    root=reBalanceFactor(&node50);
    TEST_ASSERT_EQUAL_NODE(root,&node20,&node70,0);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);

}

/**
*                 40(1)                               40(0)
*                 /  \           rebalance            /   \
*             25(2)   50(1)       ----->          25(0)   50(1)
*              /  \      \                         /  \     \
*           10(0)  30(0) 60(0)                 10(0) 30(0) 60(0)
*
*
**/

void test_reBalanceFactor_given_25_10_40_30_50_add_60(void){
    //Build number tree
    initNode(&node60,NULL,NULL,0);
    initNode(&node30,NULL,NULL,0);
    initNode(&node50,NULL,&node60,1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node25,&node10,&node30,2);
    initNode(&node40,&node25,&node50,1);

    //Test
    root=reBalanceFactor(&node40);
    TEST_ASSERT_EQUAL_NODE(root,&node25,&node50,0);
    TEST_ASSERT_EQUAL_NODE(&node25,&node10,&node30,0);
    TEST_ASSERT_EQUAL_NODE(&node50,NULL,&node60,1);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);

}

/**
*            50(-1)
*           /   \
*         30(0)  60(0)
*        /  \
*     20(0)  40(0)
*
*
**/

void test_AvlAdd_given_50_30_20_40_60_add_30_expected_error(void){
    initNode(&node10,&node1,&node10,77);
    initNode(&node20,NULL,NULL,0);
    initNode(&node40,NULL,NULL,0);
    initNode(&node30,&node20,&node40,0);
    initNode(&node60,NULL,NULL,0);
    initNode(&node50,&node30,&node60,-1);

    //Test
    Try{
        root=avlAdd(&node50,&node30);
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_SAME_NODE, ex->errorCode);
    }

}
