#include "unity.h"
#include "AvlAdd.h"
#include "AvlDelete.h"
#include "Node.h"
#include "CustomAssert.h"
#include "Rotate.h"
#include "Balance.h"
#include "Exception.h"
#include "Error.h"
#include "CException.h"

CEXCEPTION_T ex;
Node * root;
Node * replacedNode;
Node * deletedNode;
int  heightDec;
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
//////////////Avl Delete without same Root inside Rotate/////////////////////////////////////////////////////
/**
*             80(-1)
*           /       \
*         40(0)     90(1)         --->         ERROR!
*        /    \         \        remove  85
*      10(-1)  60(0)  99(0)
*        /       /  \
*      1(0)   50(0) 70(0)
**/

void test_AvlDelete_given_WO_5_30_20_25_35_40_45_50_1_delete_85_expect_error(void){
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
    Try{
        root=avlDelete(&node80,85);
        TEST_FAIL_MESSAGE("Expecting exeception to be thrown.");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_NODE_NOT_FOUND, ex->errorCode);
    }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////AVL Delete node without children////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
// it can be notice that if children is -1 or 1 the parent node wont change on balanceFactor
// this is because when children change from 0 -> 1 due to grandchildren , the height on parent on left or right
// still remain as same before deleting the node
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
    Try{
        root=avlDelete(&node80,1);
        TEST_ASSERT_EQUAL_PTR(&node80,root);
        TEST_ASSERT_EQUAL_NODE(root,&node40,&node90,-1);
        TEST_ASSERT_EQUAL_NODE(&node40,&node10,&node60,1);
        TEST_ASSERT_EQUAL_NODE(&node60,&node50,&node70,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,&node99,1);
        TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node99,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/**
*       30(1)                     30(1)
*       /   \         delete      /  \
*     5(0)  70(0)     ---->   5(0)    70(1)
*          /   \         65              \
*        65(0) 75(0)                    75(0)
*
**/

void test_AvlDelete_given_WO_5_30_70_65_75_delete_65(void){
    //Build number tree
    initNode(&node5,NULL,NULL,0);
    initNode(&node65,NULL,NULL,0);
    initNode(&node75,NULL,NULL,0);
    initNode(&node70,&node65,&node75,0);
    initNode(&node30,&node5,&node70,1);

    //Test
    Try{
        root=avlDelete(&node30,65);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node5,&node70,1);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,&node75,1);
        TEST_ASSERT_EQUAL_NODE(&node5,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node75,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/**
*       30(1)                     30(1)
*       /   \         delete      /  \
*     5(0)  70(0)     ---->   5(0)    70(-1)
*          /   \         75            /
*        65(0) 75(0)                 65(0)
*
**/

void test_AvlDelete_given_WO_5_30_70_65_75_delete_75(void){
    //Build number tree
    initNode(&node5,NULL,NULL,0);
    initNode(&node65,NULL,NULL,0);
    initNode(&node75,NULL,NULL,0);
    initNode(&node70,&node65,&node75,0);
    initNode(&node30,&node5,&node70,1);

    //Test
    Try{
        root=avlDelete(&node30,75);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node5,&node70,1);
        TEST_ASSERT_EQUAL_NODE(&node70,&node65,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node5,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node75,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/**
*       30(1)                     30(0)
*       /   \         delete      /  \
*     5(0)  70(1)     ---->   5(0)    70(0)
*              \         85
*             85(0)
*
**/

void test_AvlDelete_given_WO_5_30_70_85_delete_85(void){
    //Build number tree
    initNode(&node5,NULL,NULL,0);
    initNode(&node75,NULL,NULL,0);
    initNode(&node70,NULL,&node85,1);
    initNode(&node30,&node5,&node70,1);

    //Test
    Try{
        root=avlDelete(&node30,85);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node5,&node70,0);
        TEST_ASSERT_EQUAL_NODE(&node5,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*       30(-1)                     30(0)
*       /   \         delete      /  \
*     5(-1)  70(0)     ---->   5(0)    70(0)
*      /                 1
*    1(0)
*
**/

void test_AvlDelete_given_WO_5_30_70_1_delete_1(void){
    //Build number tree
    initNode(&node1,NULL,NULL,0);
    initNode(&node5,&node1,NULL,-1);
    initNode(&node70,NULL,NULL,0);
    initNode(&node30,&node5,&node70,-1);

    //Test
    Try{
        root=avlDelete(&node30,1);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node5,&node70,0);
        TEST_ASSERT_EQUAL_NODE(&node5,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*       30(-1)                     30(-1)
*       /   \         delete      /   \
*     10(0)  70(0)     ---->   10(1)   70(0)
*      /  \               1      \
*    1(0)  15(0)                 15(0)
*
**/

void test_AvlDelete_given_WO_15_10_30_70_1_delete_1(void){
    //Build number tree
    initNode(&node1,NULL,NULL,0);
    initNode(&node15,NULL,NULL,0);
    initNode(&node10,&node1,&node15,0);
    initNode(&node70,NULL,NULL,0);
    initNode(&node30,&node10,&node70,-1);

    //Test
    Try{
        root=avlDelete(&node30,1);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node10,&node70,-1);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,&node15,1);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*       30(-1)                     30(-1)
*       /   \         delete      /   \
*     10(0)  70(0)     ---->   10(-1)   70(0)
*      /  \               15     /
*    1(0)  15(0)               1(0)
*
**/

void test_AvlDelete_given_WO_15_10_30_70_1_delete_15(void){
    //Build number tree
    initNode(&node1,NULL,NULL,0);
    initNode(&node15,NULL,NULL,0);
    initNode(&node10,&node1,&node15,0);
    initNode(&node70,NULL,NULL,0);
    initNode(&node30,&node10,&node70,-1);

    //Test
    Try{
        root=avlDelete(&node30,15);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node10,&node70,-1);
        TEST_ASSERT_EQUAL_NODE(&node10,&node1,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/////////////Avl Delete with LEFT Rotation//////////////////////////////////////////////////

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
    initNode(&node65,NULL,NULL,0);
    initNode(&node75,NULL,NULL,0);
    initNode(&node70,&node65,&node75,0);
    initNode(&node30,&node5,&node70,1);

    //Test
    Try{
        root=avlDelete(&node30,5);
        TEST_ASSERT_EQUAL_PTR(&node70,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node75,-1);
        TEST_ASSERT_EQUAL_NODE(&node30,NULL,&node65,1);
        TEST_ASSERT_EQUAL_NODE(&node65,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node75,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

/**
*       30(1)                         30(2)                                70(-1)
*       /   \         delete         /   \              rotate             /   \
*     5(-1)  70(0)     ---->      5(0)   70(0)            ----->         30(1)  75(1)
*     /     /   \         1            /    \           LEFT            /   \     \
*   1(0) 65(-1) 75(1)                65(-1) 75(1)                    5(0)  65(-1)  80(0)
*        /       \                   /       \                             /
*      60(0)    80(0)               60(0)    80(0)                        60(0)
**/

void test_AvlDelete_given_L_5_30_70_65_75_delete_1(void){
    //Build number tree
    initNode(&node1,NULL,NULL,0);
    initNode(&node60,NULL,NULL,0);
    initNode(&node80,NULL,NULL,0);
    initNode(&node5,&node1,NULL,-1);
    initNode(&node65,&node60,NULL,-1);
    initNode(&node75,NULL,&node80,1);
    initNode(&node70,&node65,&node75,0);
    initNode(&node30,&node5,&node70,1);

    //Test
    Try{
        root=avlDelete(&node30,1);
        TEST_ASSERT_EQUAL_PTR(&node70,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node75,-1);
        TEST_ASSERT_EQUAL_NODE(&node30,&node5,&node65,1);
        TEST_ASSERT_EQUAL_NODE(&node65,&node60,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node75,NULL,&node80,1);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node80,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

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
    Try{
        root=avlDelete(&node10,5);
        TEST_ASSERT_EQUAL_PTR(&node25,root);
        TEST_ASSERT_EQUAL_NODE(root,&node10,&node35,0);
        TEST_ASSERT_EQUAL_NODE(&node35,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*       30(1)                     30(2)                                70(0)
*       /   \         delete        \              rotate             /   \
*     25(0)  70(1)     ---->        70(1)            ----->         30(0)  75(0)
*             \         5              \           LEFT
*             75(0)                   75(0)
*
**/

void test_AvlDelete_given_L_25_30_70_75_delete_25(void){
    //Build number tree
    initNode(&node25,NULL,NULL,0);
    initNode(&node75,NULL,NULL,0);
    initNode(&node70,NULL,&node75,1);
    initNode(&node30,&node25,&node70,1);

    //Test
    Try{
        root=avlDelete(&node30,25);
        TEST_ASSERT_EQUAL_PTR(&node70,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node75,0);
        TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node75,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

/**
*            25(1)                      25(2)                           40(0)
*           /  \                        /  \           rotate           /   \
*         10(-1) 40(1)    ------>    10(0)   40(1)       ----->       25(0)  50(1)
*         /    /  \      remove 1           /  \          LEFT         /  \     \
*       1(0) 30(0) 50(1)                30(0) 50(1)                10(0) 30(0) 60(0)
*                    \                          \
*                   60(0)                      60(0)
**/

void test_AvlDelete_given_L_25_10_40_30_50_1_delete_1(void){
    //Build number tree
    initNode(&node1,NULL,NULL,0);
    initNode(&node60,NULL,NULL,0);
    initNode(&node50,NULL,&node60,1);
    initNode(&node30,NULL,NULL,0);
    initNode(&node40,&node30,&node50,1);
    initNode(&node10,&node1,NULL,-1);
    initNode(&node25,&node10,&node40,1);

    //Test
    Try{
        root=avlDelete(&node25,1);
        TEST_ASSERT_EQUAL_PTR(&node40,root);
        TEST_ASSERT_EQUAL_NODE(root,&node25,&node50,0);
        TEST_ASSERT_EQUAL_NODE(&node25,&node10,&node30,0);
        TEST_ASSERT_EQUAL_NODE(&node50,NULL,&node60,1);
        TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*            50(1)                          50(2)                                   75(0)
*           /   \                           /    \              rotate             /     \
*         25(-1)  75(1)      --->        25(0)    75(1)          ----->          50(0)     85(-1)
*         /       /  \      remove 5              /    \                          / \       /
*      20(0)  60(0)  85(-1)                    60(0)   85(-1)     LEFT        25(0)  60(0) 80(0)
*                    /                               /
*                   80(0)                          80(0)
**/

void test_AvlDelete_given_L_50_25_75_60_85_20_remove_20(void){
    initNode(&node20,NULL,NULL,0);
    initNode(&node80,NULL,NULL,0);
    initNode(&node85,&node80,NULL,-1);
    initNode(&node60,NULL,NULL,0);
    initNode(&node75,&node60,&node85,1);
    initNode(&node25,&node20,NULL,-1);
    initNode(&node50,&node25,&node75,1);

    //Test
    Try{
        root=avlDelete(&node50,20);
        TEST_ASSERT_EQUAL_PTR(&node75,root);
        TEST_ASSERT_EQUAL_NODE(root,&node50,&node85,0);
        TEST_ASSERT_EQUAL_NODE(&node50,&node25,&node60,0);
        TEST_ASSERT_EQUAL_NODE(&node85,&node80,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node25,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node80,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}


//////////////Avl Delete with RIGHT LEFT Rotation//////////////////////////////////////////////////
/**
*            25(1)                            25(2)                                   30(0)
*           /   \                           /      \              rotate             /     \
*         20(-1)  40(-1)      --->        20(0)    40(-1)          ----->         25(-1)   40(0)
*         /       /  \      remove 15              /    \         RIGHT           /        /  \
*      15(0)    30(1) 50(0)                    30(1)    50(0)     LEFT          20(0)    35(0) 50(0)
*                \                              \
*                 35(0)                         35(0)
**/

void test_AvlDelete_given_RL_15_20_25_30_35_40_50_remove_15(void){
    initNode(&node15,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node30,NULL,&node35,1);
    initNode(&node40,&node30,&node50,-1);
    initNode(&node20,&node15,NULL,-1);
    initNode(&node25,&node20,&node40,1);

    //Test
    Try{
        root=avlDelete(&node25,15);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node25,&node40,0);
        TEST_ASSERT_EQUAL_NODE(&node25,&node20,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node40,&node35,&node50,0);
        TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node35,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*            20(1)                            20(2)                                   35(0)
*           /   \                           /      \              rotate             /     \
*         15(-1)  40(-1)      --->        15(0)    40(-1)          ----->         20(0)   40(1)
*         /       /  \      remove 10              /    \         RIGHT           /    \     \
*      10(0)    35(-1) 50(0)                    35(-1)    50(0)    LEFT        15(0) 30(0)   50(0)
*               /                              /
*              30(0)                         30(0)
**/

void test_AvlDelete_given_RL_10_15_20_30_35_40_50_remove_10(void){
    initNode(&node10,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node30,NULL,NULL,0);
    initNode(&node35,&node30,NULL,-1);
    initNode(&node40,&node35,&node50,-1);
    initNode(&node15,&node10,NULL,-1);
    initNode(&node20,&node15,&node40,1);

    //Test
    Try{
        root=avlDelete(&node20,10);
        TEST_ASSERT_EQUAL_PTR(&node35,root);
        TEST_ASSERT_EQUAL_NODE(root,&node20,&node40,0);
        TEST_ASSERT_EQUAL_NODE(&node20,&node15,&node30,0);
        TEST_ASSERT_EQUAL_NODE(&node40,NULL,&node50,1);
        TEST_ASSERT_EQUAL_NODE(&node15,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

//////////////Avl Delete with RIGHT Rotation//////////////////////////////////////////////////

/**
*       50(-1)                        50(-2)                             30(1)
*       /   \         delete          /              rotate             /   \
*     30(0)  70(0)     ---->        30(0)            ----->         20(0)   50(-1)
*     /   \             70         /    \           RIGHT                     /
*   20(0) 45(0)                  20(0) 45(0)                              45(0)
*
**/

void test_AvlDelete_given_R_50_30_70_20_45_delete_70(void){
    //Build number tree
    initNode(&node45,NULL,NULL,0);
    initNode(&node20,NULL,NULL,0);
    initNode(&node30,&node20,&node45,0);
    initNode(&node70,NULL,NULL,0);
    initNode(&node50,&node30,&node70,-1);

    //Test
    Try{
        root=avlDelete(&node50,70);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node20,&node50,1);
        TEST_ASSERT_EQUAL_NODE(&node50,&node45,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node45,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

/**
*       85(-1)                         85(-2)                                70(1)
*       /    \         delete         /   \              rotate             /   \
*      70(0) 90(1)    ---->        70(0)   90(0)         ----->         65(-1)  85(-1)
*     /   \     \      99         /    \                 RIGHT          /      /    \
*  65(-1) 75(1)  99(0)          65(-1) 75(1)                         60(0)  75(1)  90(0)
*   /       \                   /       \                                      \
*  60(0)    80(0)             60(0)    80(0)                                  80(0)
**/

void test_AvlDelete_given_R_60_65_70_75_80_85_90_99_delete_99(void){
    //Build number tree
    initNode(&node99,NULL,NULL,0);
    initNode(&node60,NULL,NULL,0);
    initNode(&node80,NULL,NULL,0);
    initNode(&node90,NULL,&node99,1);
    initNode(&node65,&node60,NULL,-1);
    initNode(&node75,NULL,&node80,1);
    initNode(&node70,&node65,&node75,0);
    initNode(&node85,&node70,&node90,-1);

    //Test
    Try{
        root=avlDelete(&node85,99);
        TEST_ASSERT_EQUAL_PTR(&node70,root);
        TEST_ASSERT_EQUAL_NODE(root,&node65,&node85,1);
        TEST_ASSERT_EQUAL_NODE(&node85,&node75,&node90,-1);
        TEST_ASSERT_EQUAL_NODE(&node65,&node60,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node75,NULL,&node80,1);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}
/**
*      60(-1)                     60(-2)                            50(0)
*       /   \                    /              rotate             /      \
*   50(-1)  70(0)    --->     50(-1)           ----->           40(0)    60(0)
*    /             delete70    /                RIGHT
*  40(0)                     40(0)
*
**/

void test_AvlDelete_given_R_60_50_40_70_delete_70(void){
    initNode(&node40,NULL,NULL,0);
    initNode(&node70,NULL,NULL,0);
    initNode(&node50,&node40,NULL,-1);
    initNode(&node60,&node50,&node70,-1);

    //Test
    Try{
        root=avlDelete(&node60,70);
        TEST_ASSERT_EQUAL_PTR(&node50,root);
        TEST_ASSERT_EQUAL_NODE(root,&node40,&node60,0);
        TEST_ASSERT_EQUAL_NODE(&node40,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*       50(-1)                               50(-2)                            30(0)
*      /      \                              /   \          rotate             /   \
*     30(-1)  60(1)     --------->       30(-1)  60(0)      ----->          20(-1)  50(0)
*     /    \     \       remove 70         /  \             RIGHT           /     /     \
*  20(-1) 40(0)  70(0)                  20(-1)  40(0)                     10(0) 40(0)  60(0)
*    /                                  /
*   10(0)                            10(0)
**/

void test_avlDelete_given_R_50_30_20_40_60_10(void){
    initNode(&node70,NULL,NULL,0);
    initNode(&node40,NULL,NULL,0);
    initNode(&node10,NULL,NULL,0);
    initNode(&node60,NULL,&node70,1);
    initNode(&node20,&node10,NULL,-1);
    initNode(&node30,&node20,&node40,-1);
    initNode(&node50,&node30,&node60,-1);

    //Test
    Try{
        root=avlDelete(&node50,70);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node20,&node50,0);
        TEST_ASSERT_EQUAL_NODE(&node20,&node10,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node50,&node40,&node60,0);
        TEST_ASSERT_EQUAL_NODE(&node40,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

/**
*       50(-1)                               50(-2)                            30(0)
*      /      \                              /   \          rotate             /   \
*     30(-1)  60(1)     --------->       30(-1)  60(0)      ----->          20(1)  50(0)
*     /    \     \       remove 70         /  \             RIGHT           \     /     \
*  20(1) 40(0)  70(0)                  20(1)  40(0)                       25(0) 40(0)  60(0)
*    \                                    \
*   25(0)                                 25(0)
**/

void test_avlDelete_given_R_50_30_20_25_40_60_remove_70(void){
    initNode(&node70,NULL,NULL,0);
    initNode(&node40,NULL,NULL,0);
    initNode(&node25,NULL,NULL,0);
    initNode(&node60,NULL,&node70,1);
    initNode(&node20,NULL,&node25,1);
    initNode(&node30,&node20,&node40,-1);
    initNode(&node50,&node30,&node60,-1);

    //Test
    Try{
        root=avlDelete(&node50,70);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node20,&node50,0);
        TEST_ASSERT_EQUAL_NODE(&node20,NULL,&node25,1);
        TEST_ASSERT_EQUAL_NODE(&node50,&node40,&node60,0);
        TEST_ASSERT_EQUAL_NODE(&node40,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
//////////////Avl Delete with LEFTRIGHT Rotation//////////////////////////////////////////////////

/**
*       15(-1)                   15(-2)                            10(0)
*       /  \         delete        /           rotate             /   \
*     5(1) 25(0)     ---->      5(1)            ----->         5(0)  15(0)
*      \               25         \           LEFTRIGHT
*     10(0)                       10(0)
*
**/

void test_AvlDelete_given_LR_5_10_25_15_delete_5(void){
    //Build number tree
    initNode(&node10,NULL,NULL,0);
    initNode(&node5,NULL,&node10,1);
    initNode(&node25,NULL,NULL,0);
    initNode(&node15,&node5,&node25,-1);

    //Test
    Try{
        root=avlDelete(&node15,25);
        TEST_ASSERT_EQUAL_PTR(&node10,root);
        TEST_ASSERT_EQUAL_NODE(root,&node5,&node15,0);
        TEST_ASSERT_EQUAL_NODE(&node5,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node15,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*        80(-1)                            80(-2)                           60(0)
*       /     \          delete           /     \         Rotate          /       \
*    30(1)   90(1)        ---->        30(1)   90(0)      ---->        30(-1)   80(0)
*   /     \     \         99          /     \           LEFTRIGHT    /        /    \
* 10(0)   60(1)  99(0)              10(0)   60(1)                  10(0)     70(0)  90(0)
*            \                                 \
*            70(0)                             70(0)
**/

void test_avlDelete_given_LR_80_30_10_60_90_70_99_remove99(void){
    initNode(&node70,NULL,NULL,0);
    initNode(&node99,NULL,NULL,0);
    initNode(&node60,NULL,&node70,1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,1);
    initNode(&node90,NULL,&node99,1);
    initNode(&node80,&node30,&node90,-1);

    //Test
    Try{
        root=avlDelete(&node80,99);
        TEST_ASSERT_EQUAL_PTR(&node60,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node80,0);
        TEST_ASSERT_EQUAL_NODE(&node30,&node10,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node80,&node70,&node90,0);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/**
*        80(-1)                            80(-2)                           60(0)
*       /     \          delete           /     \         Rotate          /       \
*    30(1)   90(1)        ---->        30(1)   90(0)      ---->        30(-1)   80(0)
*   /     \     \         99          /     \           LEFTRIGHT    /    \         \
* 10(0)   60(-1)  99(0)              10(0)   60(-1)                  10(0) 50(0)    90(0)
*          /                                 /
*         50(0)                            50(0)
**/
void test_avlDelete_given_LR_80_30_10_60_90_50_99_remove_99(void){
    initNode(&node99,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node60,&node50,NULL,-1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,1);
    initNode(&node90,NULL,&node99,1);
    initNode(&node80,&node30,&node90,-2);

    //Test
    Try{
        root=avlDelete(&node80,99);
        TEST_ASSERT_EQUAL_PTR(&node60,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node80,0);
        TEST_ASSERT_EQUAL_NODE(&node30,&node10,&node50,0);
        TEST_ASSERT_EQUAL_NODE(&node80,NULL,&node90,1);
        TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////AVL Delete node with left children only ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

///WITHOUT Rotation
/**
*        80(-1)                            80(0)
*       /     \          delete           /     \
*    30(1)   90(1)        ---->        30(0)   90(1)
*   /     \     \           60         /    \     \
* 10(0)   60(-1)  99(0)              10(0)  50(0) 99(0)
*          /
*         50(0)
**/
void test_avlDelete_given_LeftChild_WO_80_30_10_60_90_50_99_remove_60(void){
    initNode(&node99,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node60,&node50,NULL,-1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,1);
    initNode(&node90,NULL,&node99,1);
    initNode(&node80,&node30,&node90,-1);

    //Test
    Try{
        root=avlDelete(&node80,60);
        TEST_ASSERT_EQUAL_PTR(&node80,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node90,0);
        TEST_ASSERT_EQUAL_NODE(&node30,&node10,&node50,0);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,&node99,1);
        TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///AVL Delete node with right children that has no left children ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*        80(-1)                            80(-1)
*       /     \          delete           /     \
*    30(1)   90(1)        ---->        30(1)   90(1)
*   /     \     \           60         /    \     \
* 10(0)   60(0)  99(0)              10(0)  65(-1) 99(0)
*          /   \                            /
*         50(0) 65(0)                     50(0)
**/
void test_avlDelete_given_RightChildOnly_WO_80_30_10_60_65_90_50_99_remove_60(void){
    initNode(&node99,NULL,NULL,0);
    initNode(&node65,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node60,&node50,&node65,0);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,1);
    initNode(&node90,NULL,&node99,1);
    initNode(&node80,&node30,&node90,-1);


    Try{
        root=avlDelete(&node80,60);
        TEST_ASSERT_EQUAL_PTR(&node80,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node90,-1);
        TEST_ASSERT_EQUAL_NODE(&node30,&node10,&node65,1);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,&node99,1);
        TEST_ASSERT_EQUAL_NODE(&node65,&node50,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*        80(-1)                            80(0)
*       /     \          delete           /     \
*    30(1)   90(1)        ---->        30(0)   90(1)
*   /     \     \         60          /     \     \
* 10(0)   60(1)  99(0)              10(0)   70(0)  99(0)
*            \
*            70(0)
**/

void test_avlDelete_given_RightChildOnly_WO_80_30_10_60_90_70_99_remove60(void){
    initNode(&node70,NULL,NULL,0);
    initNode(&node99,NULL,NULL,0);
    initNode(&node60,NULL,&node70,1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,1);
    initNode(&node90,NULL,&node99,1);
    initNode(&node80,&node30,&node90,-1);

    //Test
    Try{
        root=avlDelete(&node80,60);
        TEST_ASSERT_EQUAL_PTR(&node80,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node90,0);
        TEST_ASSERT_EQUAL_NODE(&node30,&node10,&node70,0);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,&node99,1);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node99,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///AVL Delete node with right children that has left children ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*        80(-1)                            80(-1)
*       /     \          delete           /     \
*    30(1)   90(1)        ---->        50(1)   90(1)
*   /     \     \           30         /    \     \
* 10(0)   60(0)  99(0)              10(0)  60(1) 99(0)
*          /   \                              \
*         50(0) 65(0)                         65(0)
**/
void test_avlDelete_given_RightLEFTChild_WO_80_30_10_60_65_90_50_99_remove_30(void){
    initNode(&node99,NULL,NULL,0);
    initNode(&node65,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node60,&node50,&node65,0);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,1);
    initNode(&node90,NULL,&node99,1);
    initNode(&node80,&node30,&node90,-1);


    Try{
        root=avlDelete(&node80,30);
        TEST_ASSERT_EQUAL_PTR(&node80,root);
        TEST_ASSERT_EQUAL_NODE(root,&node50,&node90,-1);
        TEST_ASSERT_EQUAL_NODE(&node50,&node10,&node60,1);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,&node99,1);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,&node65,1);
        TEST_ASSERT_EQUAL_NODE(&node65,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node99,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///avlGetReplacer /////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Replace first right then left until the end
//avlGetReplacer (rightroot,heightChange,replacedNode)


/**
*    30(1)                                     50(1)
*   /     \                                   /   \
* 10(0)   60(0)              --->           10(0)  60(1)
*          /   \           remove 30                 \
*         50(0) 65(0)      get replacer              65(0)
*                         from right left
*                          node(50)
**/
void test_avlGetReplacer_given_RightLEFTChild_10_30_50_65_60_remove_30(void){
    initNode(&node10,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node65,NULL,NULL,0);
    initNode(&node60,&node50,&node65,0);
    initNode(&node30,&node10,&node60,1);

    Try{
        root=avlGetReplacer(&node60,&heightDec,&replacedNode);
        TEST_ASSERT_EQUAL_PTR(&node60,root);
        TEST_ASSERT_EQUAL_PTR(&node50,replacedNode);
        TEST_ASSERT_EQUAL_NODE(root,NULL,&node65,1);
        TEST_ASSERT_EQUAL_NODE(&node65,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*    30(1)                                     60(0)
*   /     \                                   /   \
* 10(0)   60(1)              --->           10(0)  65(0)
*             \           remove 30
*            65(0)      get replacer
*                         from right
*                          node(60)
**/
void test_avlGetReplacer_given_RightChild_10_30_65_60_remove_30(void){
    initNode(&node10,NULL,NULL,0);
    initNode(&node65,NULL,NULL,0);
    initNode(&node60,NULL,&node65,1);
    initNode(&node30,&node10,&node60,1);

    Try{
        root=avlGetReplacer(&node60,&heightDec,&replacedNode);
        TEST_ASSERT_EQUAL_PTR(&node65,root);
        TEST_ASSERT_EQUAL_PTR(&node60,replacedNode);
        TEST_ASSERT_EQUAL_NODE(&node65,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}


/**
*    30(1)                                     50(1)
*   /     \                                   /    \
* 10(-1)   60(-1)              --->         10(0)  60(0)
* /        /   \           remove 30        /       /  \
* 5(0)   50(1) 65(0)      get replacer    5(0)   55(0) 65(0)
*           \              from right left
*           55(0)              node(50)
**/
void test_avlGetReplacer_given_RLRChild_WO_5_10_30_50_55_60_65_remove_30(void){
    initNode(&node10,&node5,NULL,-1);
    initNode(&node55,NULL,NULL,0);
    initNode(&node50,NULL,&node55,1);
    initNode(&node65,NULL,NULL,0);
    initNode(&node60,&node50,&node65,-1);
    initNode(&node30,&node10,&node60,1);

    Try{
        root=avlGetReplacer(&node60,&heightDec,&replacedNode);
        TEST_ASSERT_EQUAL_PTR(&node60,root);
        TEST_ASSERT_EQUAL_PTR(&node50,replacedNode);
        TEST_ASSERT_EQUAL_NODE(root,&node55,&node65,0);
        TEST_ASSERT_EQUAL_NODE(&node65,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node55,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*    30(1)                                     50(0)
*   /     \                                   /    \
* 10(-1)   60(1)              --->         10(0)   65(0)
* /        /   \           remove 30        /       /  \
* 5(0)   50(0) 65(1)      get replacer    5(0)   60(0) 70(0)
*                \        from right left
*               70(0)        node(50)
**/
void test_avlGetReplacer_given_RLRChild_5_10_30_50_70_60_65_remove_30(void){
    initNode(&node10,&node5,NULL,-1);
    initNode(&node55,NULL,NULL,0);
    initNode(&node65,NULL,&node70,1);
    initNode(&node50,NULL,NULL,0);
    initNode(&node60,&node50,&node65,1);
    initNode(&node30,&node10,&node60,1);

    Try{
        root=avlGetReplacer(&node60,&heightDec,&replacedNode);
        TEST_ASSERT_EQUAL_PTR(&node65,root);
        TEST_ASSERT_EQUAL_PTR(&node50,replacedNode);
        TEST_ASSERT_EQUAL_NODE(root,&node60,&node70,0);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
///Rotate and Rebalance for Delete //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////ROTATE RIGHT AND REBALANCE FOR DELETE//////////////////////////////////////////////////

// ROTATE RIGHT AND REBALANCE
/**
*          30(-2)                            20(0)
*        /              rotate             /      \
*      20(-1)           ----->           10(0)    30(0)
*    /                  RIGHT
*  10(0)
*
**/

void test_rotateRightAndReBalanceForDelete_given_30_20_10(void){
    initNode(&node10,NULL,NULL,0);
    initNode(&node20,&node10,NULL,-1);
    initNode(&node30,&node20,NULL,-2);

    //Test
    Try{
        root=rotateRightAndReBalanceForDelete(&node30);
        TEST_ASSERT_EQUAL_PTR(&node20,root);
        TEST_ASSERT_EQUAL_NODE(root,&node10,&node30,0);
        TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

/**
*        60(-2)                              40(1)
*          /              rotate             /   \
*        40(0)            ----->         30(0)   60(-1)
*      /    \           RIGHT                     /
*    30(0) 55(0)                              55(0)
*
**/

void test_rotateRightAndReBalanceForDelete_given_30_40_55_60(void){
    //Build number tree
    initNode(&node55,NULL,NULL,0);
    initNode(&node30,NULL,NULL,0);
    initNode(&node40,&node30,&node55,0);
    initNode(&node60,&node40,NULL,-2);

    //Test
    Try{
        root=rotateRightAndReBalanceForDelete(&node60);
        TEST_ASSERT_EQUAL_PTR(&node40,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node60,1);
        TEST_ASSERT_EQUAL_NODE(&node60,&node55,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node55,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

/**
*       85(-2)                                70(1)
*        /   \              rotate             /   \
*     70(0)   90(0)         ----->         65(-1)  85(-1)
*      /    \                 RIGHT          /      /    \
*   65(-1) 75(1)                         60(0)  75(1)  90(0)
*    /       \                                      \
*   60(0)    80(0)                                  80(0)
**/

void test_rotateRightAndReBalanceForDelete_given_60_65_70_75_80_85_90_99(void){
    //Build number tree
    initNode(&node60,NULL,NULL,0);
    initNode(&node80,NULL,NULL,0);
    initNode(&node90,NULL,NULL,0);
    initNode(&node65,&node60,NULL,-1);
    initNode(&node75,NULL,&node80,1);
    initNode(&node70,&node65,&node75,0);
    initNode(&node85,&node70,&node90,-2);

    //Test
    Try{
        root=rotateRightAndReBalanceForDelete(&node85);
        TEST_ASSERT_EQUAL_PTR(&node70,root);
        TEST_ASSERT_EQUAL_NODE(root,&node65,&node85,1);
        TEST_ASSERT_EQUAL_NODE(&node85,&node75,&node90,-1);
        TEST_ASSERT_EQUAL_NODE(&node65,&node60,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node75,NULL,&node80,1);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

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

void test_rotateRightAndReBalanceForDelete_given_50_30_20_40_60_10(void){
    initNode(&node20,NULL,NULL,0);
    initNode(&node30,&node20,NULL,-1);
    initNode(&node50,NULL,NULL,0);
    initNode(&node40,&node30,&node50,-1);
    initNode(&node70,NULL,NULL,0);
    initNode(&node60,&node40,&node70,-2);

    //Test
    Try{
        root=rotateRightAndReBalanceForDelete(&node60);
        TEST_ASSERT_EQUAL_PTR(&node40,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node60,0);
        TEST_ASSERT_EQUAL_NODE(&node30,&node20,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node60,&node50,&node70,0);
        TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

/**
*            40(-2)                            30(0)
*           /   \          rotate             /     \
*         30(-1) 50(0)   ----->           15(1)    40(0)
*        /  \             RIGHT            \        /   \
*     15(1) 35(0)      rebalance         20(0)     35(0) 50(0)
*        \
*      20(0)
**/

void test_rotateRightAndReBalanceForDelete_given_20_15_30_35_40_50(void){
    initNode(&node20,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node15,NULL,&node20,1);
    initNode(&node30,&node15,&node35,-1);
    initNode(&node50,NULL,NULL,0);
    initNode(&node40,&node30,&node50,-2);

    //Test
    Try{
        root=rotateRightAndReBalanceForDelete(&node40);
        TEST_ASSERT_EQUAL_PTR(&node30,root);
        TEST_ASSERT_EQUAL_NODE(root,&node15,&node40,0);
        TEST_ASSERT_EQUAL_NODE(&node15,NULL,&node20,1);
        TEST_ASSERT_EQUAL_NODE(&node40,&node35,&node50,0);
        TEST_ASSERT_EQUAL_NODE(&node35,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

// ROTATE LEFT RIGHT AND REBALANCE


/**
*        80(-2)                            60(0)
*       /     \          Rotate          /       \
*    30(1)   90(0)        ---->        30(-1)   80(0)
*   /     \             LEFTRIGHT     /        /    \
* 10(0)   60(1)        rebalance   10(0)     70(0)  90(0)
*            \
*            70(0)
**/

void test_rotateRightAndReBalanceForDelete_given_80_30_10_60_90_70(void){
    initNode(&node70,NULL,NULL,0);
    initNode(&node60,NULL,&node70,1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,1);
    initNode(&node90,NULL,NULL,0);
    initNode(&node80,&node30,&node90,-2);

    //Test
    Try{
        root=rotateRightAndReBalanceForDelete(&node80);
        TEST_ASSERT_EQUAL_PTR(&node60,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node80,0);
        TEST_ASSERT_EQUAL_NODE(&node30,&node10,NULL,-1);
        TEST_ASSERT_EQUAL_NODE(&node80,&node70,&node90,0);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*        80(-2)                            60(0)
*       /     \          Rotate          /       \
*    30(1)  90(0)        ---->         30(0)   80(1)
*   /     \             LEFTRIGHT     /   \       \
* 10(0)   60(-1)        rebalance   10(0) 50(0)  90(0)
*         /
*       50(0)
**/

void test_rotateRightAndReBalanceForDelete_given_80_30_10_60_90_50(void){
    initNode(&node70,NULL,NULL,0);
    initNode(&node60,&node50,NULL,-1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,1);
    initNode(&node90,NULL,NULL,0);
    initNode(&node80,&node30,&node90,-2);

    //Test
    Try{
        root=rotateRightAndReBalanceForDelete(&node80);
        TEST_ASSERT_EQUAL_PTR(&node60,root);
        TEST_ASSERT_EQUAL_NODE(root,&node30,&node80,0);
        TEST_ASSERT_EQUAL_NODE(&node30,&node10,&node50,0);
        TEST_ASSERT_EQUAL_NODE(&node80,NULL,&node90,1);
        TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node90,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}

/**
*        30(-2)
*         /        Rotate        25(0)
*       20(1)       ---->        /  \
*        \       LEFTRIGHT     20(0) 30(0)
*       25(0)
*
**/
void test_rotateRightAndReBalanceForDelete_25_30_20(void){
    //Build number tree
    initNode(&node25,NULL,NULL,0);
    initNode(&node20,NULL,&node25,1);
    initNode(&node30,&node20,NULL,-2);

    //Test
    Try{
      root=rotateRightAndReBalanceForDelete(&node30);
      TEST_ASSERT_EQUAL_PTR(&node25,root);
      TEST_ASSERT_EQUAL_NODE(root,&node20,&node30,0);
      TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
      TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }
}
//////////////ROTATE LEFT AND REBALANCE//////////////////////////////////////////////////

// ROTATE LEFT AND REBALANCE
/**
*              35(2)                           50(0)
*              /  \           rotate           /   \
*         20(0)   50(1)       ----->       35(0)    60(1)
*                /  \          LEFT         /  \     \
*            40(0) 60(1)     rebalance   20(0) 40(0) 70(0)
*                      \
*                     70(0)
**/

void test_rotateLeftAndReBalanceForDelete_given_35_20_50_40_60_70(void){
    //Build number tree
    initNode(&node70,NULL,NULL,0);
    initNode(&node60,NULL,&node70,1);
    initNode(&node40,NULL,NULL,0);
    initNode(&node50,&node40,&node60,1);
    initNode(&node20,NULL,NULL,0);
    initNode(&node35,&node20,&node50,2);

    //Test
    Try{
        root=rotateLeftAndReBalanceForDelete(&node35);
        TEST_ASSERT_EQUAL_PTR(&node50,root);
        TEST_ASSERT_EQUAL_NODE(root,&node35,&node60,0);
        TEST_ASSERT_EQUAL_NODE(&node35,&node20,&node40,0);
        TEST_ASSERT_EQUAL_NODE(&node60,NULL,&node70,1);
        TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node40,NULL,NULL,0);
        TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
    }Catch(ex) {
        dumpException(ex);
        TEST_FAIL_MESSAGE("Do not expect any exception to be thrown");
    }

}

/**
*                 25(2)                             40(0)
*                 /  \            rotate            /   \
*             10(0)   40(1)       ----->        25(0)   50(1)
*                     /  \         LEFT          /  \     \
*                  30(0) 60(-1)    rebalance    10(0) 30(0) 60(0)
*                         /
*                       50(0)
**/

void test_rotateLeftAndReBalanceForDelete_given_25_10_40_30_50_60(void){
    //Build number tree
    initNode(&node60,NULL,NULL,0);
    initNode(&node50,NULL,&node60,1);
    initNode(&node30,NULL,NULL,0);
    initNode(&node40,&node30,&node50,1);
    initNode(&node10,NULL,NULL,0);
    initNode(&node25,&node10,&node40,2);

    //Test
    root=rotateLeftAndReBalanceForDelete(&node25);
    TEST_ASSERT_EQUAL_PTR(&node40,root);
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

void test_rotateLeftAndReBalanceForDelete_given_20_50_70(void){
    //Build number tree
    initNode(&node70,NULL,NULL,0);
    initNode(&node50,NULL,&node70,1);
    initNode(&node20,NULL,&node50,2);

    //Test
    root=rotateLeftAndReBalanceForDelete(&node20);
    TEST_ASSERT_EQUAL_PTR(&node50,root);
    TEST_ASSERT_EQUAL_NODE(root,&node20,&node70,0);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node70,NULL,NULL,0);
}

/**
*            50(2)                                   75(0)
*           /    \              rotate             /     \
*       25(0)    75(1)          ----->          50(0)     85(-1)
*                /    \                          / \       /
*             60(0)   85(-1)    LEFT         25(0)  60(0) 80(0)
*                      /       rebalance
*                    80(0)
**/

void test_rotateLeftAndReBalanceForDelete_given_50_25_75_60_85_80(void){
    initNode(&node85,&node80,NULL,-1);
    initNode(&node80,NULL,NULL,0);
    initNode(&node60,NULL,NULL,0);
    initNode(&node75,&node60,&node85,1);
    initNode(&node25,NULL,NULL,0);
    initNode(&node50,&node25,&node75,2);

    //Test
    root=rotateLeftAndReBalanceForDelete(&node50);
    TEST_ASSERT_EQUAL_PTR(&node75,root);
    TEST_ASSERT_EQUAL_NODE(root,&node50,&node85,0);
    TEST_ASSERT_EQUAL_NODE(&node50,&node25,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node85,&node80,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node25,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node80,NULL,NULL,0);
}

/**
*            30(2)                                     45(0)
*           /    \                 rotate             /     \
*       25(0)    45(1)             ----->          30(0)     60(1)
*                /    \                             / \        \
*             40(0)   60(1)       LEFT        25(0)  40(0)     75(0)
*                       \       rebalance
*                      75(0)
**/

void test_rotateLeftAndReBalanceForDelete_given_25_30_45_40_60_75(void){
    initNode(&node75,NULL,NULL,0);
    initNode(&node40,NULL,NULL,0);
    initNode(&node60,NULL,&node75,1);
    initNode(&node45,&node40,&node60,1);
    initNode(&node25,NULL,NULL,0);
    initNode(&node30,&node25,&node45,2);

    //Test
    root=rotateLeftAndReBalanceForDelete(&node30);
    TEST_ASSERT_EQUAL_PTR(&node45,root);
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node60,0);
    TEST_ASSERT_EQUAL_NODE(&node30,&node25,&node40,0);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,&node75,1);
    TEST_ASSERT_EQUAL_NODE(&node25,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node80,NULL,NULL,0);
}
/**
*     30(2)                                70(-1)
*       \              rotate             /   \
*       70(0)            ----->         30(1)  75(0)
*      /    \           LEFT              \
*    65(0) 75(0)                         65(0)
*
**/

void test_rotateLeftAndReBalanceForDelete_given_30_70_65_75(void){
    //Build number tree
    initNode(&node65,NULL,NULL,0);
    initNode(&node75,NULL,NULL,0);
    initNode(&node70,&node65,&node75,0);
    initNode(&node30,NULL,&node70,2);

    //Test
    root=rotateLeftAndReBalanceForDelete(&node30);
    TEST_ASSERT_EQUAL_PTR(&node70,root);
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node75,-1);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,&node65,1);
    TEST_ASSERT_EQUAL_NODE(&node65,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node75,NULL,NULL,0);

}

/**
*        30(2)                                 70(-1)
*       /   \              rotate              /   \
*     5(0)   70(0)            ----->         30(1)  75(1)
*           /    \           LEFT            /   \     \
*       65(-1) 75(1)                    5(0)  65(-1)  80(0)
*          /       \                             /
*      60(0)    80(0)                        60(0)
**/

void test_rotateLeftAndReBalanceForDelete_given_5_30_70_65_75(void){
    //Build number tree
    initNode(&node60,NULL,NULL,0);
    initNode(&node80,NULL,NULL,0);
    initNode(&node5,NULL,NULL,0);
    initNode(&node65,&node60,NULL,-1);
    initNode(&node75,NULL,&node80,1);
    initNode(&node70,&node65,&node75,0);
    initNode(&node30,&node5,&node70,2);

    //Test
    root=rotateLeftAndReBalanceForDelete(&node30);
    TEST_ASSERT_EQUAL_PTR(&node70,root);
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node75,-1);
    TEST_ASSERT_EQUAL_NODE(&node30,&node5,&node65,1);
    TEST_ASSERT_EQUAL_NODE(&node65,&node60,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node75,NULL,&node80,1);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node80,NULL,NULL,0);
}

///// ROTATE RIGHT LEFT AND REBALANCE/////////

/**
*            50(2)                                   60(0)
*           /    \              rotate             /     \
*       25(0)    75(-1)          ----->          50(0)    75(1)
*                /    \          RIGHT           / \       \
*             60(-1)  80(0)      LEFT         25(0) 55(0)  80(0)
*             /                rebalance
*           55(0)
**/

void test_rotateLeftAndReBalanceForDelete_given_RL_55_50_25_75_60_80(void){
    initNode(&node80,NULL,NULL,0);
    initNode(&node55,NULL,NULL,0);
    initNode(&node60,&node55,NULL,-1);
    initNode(&node75,&node60,&node80,-1);
    initNode(&node25,NULL,NULL,0);
    initNode(&node50,&node25,&node75,2);

    //Test
    root=rotateLeftAndReBalanceForDelete(&node50);
    TEST_ASSERT_EQUAL_PTR(&node60,root);
    TEST_ASSERT_EQUAL_NODE(root,&node50,&node75,0);
    TEST_ASSERT_EQUAL_NODE(&node50,&node25,&node55,0);
    TEST_ASSERT_EQUAL_NODE(&node75,NULL,&node80,1);
    TEST_ASSERT_EQUAL_NODE(&node25,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node55,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node80,NULL,NULL,0);
}

/**
*            50(2)                                   60(0)
*           /    \              rotate             /     \
*       25(0)    75(-1)          ----->          50(-1)    75(0)
*                /    \          RIGHT           /        /   \
*             60(1)  80(0)      LEFT         25(0)    65(0)  80(0)
*                \             rebalance
*              65(0)
**/

void test_rotateLeftAndReBalanceForDelete_given_RL_65_50_25_75_60_80(void){
    initNode(&node80,NULL,NULL,0);
    initNode(&node65,NULL,NULL,0);
    initNode(&node60,NULL,&node65,1);
    initNode(&node75,&node60,&node80,-1);
    initNode(&node25,NULL,NULL,0);
    initNode(&node50,&node25,&node75,2);

    //Test
    root=rotateLeftAndReBalanceForDelete(&node50);
    TEST_ASSERT_EQUAL_PTR(&node60,root);
    TEST_ASSERT_EQUAL_NODE(root,&node50,&node75,0);
    TEST_ASSERT_EQUAL_NODE(&node50,&node25,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node75,&node65,&node80,0);
    TEST_ASSERT_EQUAL_NODE(&node25,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node65,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node80,NULL,NULL,0);
}

/**
*      15(2)
*       \          Rotate        20(0)
*       30(-1)     ---->        /  \
*      /           RIGHT      15(0) 30(0)
*     20(0)        LEFT
*
**/
void test_rotateLeftAndReBalanceForDelete_15_30_20(void){
    //Build number tree
    initNode(&node20,NULL,NULL,0);
    initNode(&node30,&node20,NULL,-1);
    initNode(&node15,NULL,&node30,2);

    //Test
    root=rotateLeftAndReBalanceForDelete(&node15);
    TEST_ASSERT_EQUAL_PTR(&node20,root);
    TEST_ASSERT_EQUAL_NODE(root,&node15,&node30,0);
    TEST_ASSERT_EQUAL_NODE(&node15,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
}

////////////////////////////////////////////////////////////////////////////////
///node Remove and Replace//////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// When root->right == NULL
/**
*         15(-2)                 10(-1)
*         /       delete          /
*       10(-1)      --->        5(0)
*      /            15
*     5(0)
*
**/

void test_nodeRemoveAndReplace_15_10_5_del_15(void){
    //Build number tree
    initNode(&node5,NULL,NULL,0);
    initNode(&node10,&node5,NULL,-1);
    initNode(&node15,&node10,NULL,-2);

    //Test
    root=nodeRemoveAndReplace(&node15,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node10,root);
    TEST_ASSERT_EQUAL(heightDec,1);
    TEST_ASSERT_EQUAL_NODE(root,&node5,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node5,NULL,NULL,0);
}

/**
*         15(-2)                 15(-1)
*         /       delete          /
*       10(-1)      --->        10(0)
*      /            5
*     5(0)
*
**/

void test_nodeRemoveAndReplace_15_10_5_del_5(void){
    //Build number tree
    initNode(&node5,NULL,NULL,0);
    initNode(&node10,&node5,NULL,-1);
    initNode(&node15,&node10,NULL,-2);

    //Test
    root=nodeRemoveAndReplace(&node5,&heightDec);
    TEST_ASSERT_NULL(root);
    TEST_ASSERT_EQUAL(heightDec,1);
}
// When root->right not NULL
/**
*
*                       delete
*    30(1)               ---->        50(1)
*   /     \                30         /    \
* 10(0)   60(0)                    10(0)  60(1)
*          /   \                              \
*         50(0) 65(0)                         65(0)
**/
void test_nodeRemoveAndReplace_50_60_65_30_10(void){
    initNode(&node65,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node60,&node50,&node65,0);
    initNode(&node10,NULL,NULL,0);
    initNode(&node30,&node10,&node60,1);

    root=nodeRemoveAndReplace(&node30,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node50,root);
    TEST_ASSERT_EQUAL(heightDec,0); // heightDec = 0 due to no height change
    TEST_ASSERT_EQUAL_NODE(root,&node10,&node60,1);
    TEST_ASSERT_EQUAL_NODE(&node60,NULL,&node65,1);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node65,NULL,NULL,0);
}

/**
*      15(2)              20(1)
*       \       delete      \
*       30(-1)   --->      30(0)
*      /          15
*     20(0)
*
**/

void test_nodeRemoveAndReplace_15_30_20(void){
    //Build number tree
    initNode(&node20,NULL,NULL,0);
    initNode(&node30,&node20,NULL,-1);
    initNode(&node15,NULL,&node30,2);

    //Test
    root=nodeRemoveAndReplace(&node15,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node20,root);
    TEST_ASSERT_EQUAL(heightDec,1);
    TEST_ASSERT_EQUAL_NODE(root,NULL,&node30,1);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
}

/**
*      15(2)              20(2)
*       \       delete      \
*       30(0)     --->      30(1)
*      /    \      15          \
*     20(0)  35(0)             35(0)
*
**/

void test_nodeRemoveAndReplace_15_30_20_35(void){
    //Build number tree
    initNode(&node20,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node30,&node20,&node35,0);
    initNode(&node15,NULL,&node30,2);

    //Test
    root=nodeRemoveAndReplace(&node15,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node20,root);
    TEST_ASSERT_EQUAL(heightDec,0);   //heightDec == 0 due to height remain same
    TEST_ASSERT_EQUAL_NODE(root,NULL,&node30,2);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,&node35,1);
}
////////////////////////////////////////////////////////////////////////////////
///nodeSearchforDeleteNode//////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//Remark : first node (root node) cant be the node to delete
//This nodeSearchforDeleteNode will callback avlDelete to continue find the node
// which when it found the deleteNode it will call the nodeRemoveAndReplace
// automatically for node removal
// this does not rotate for the parent root
/**
*      15(1)                 15(1)
*     /  \       delete     /     \
*   10(0) 30(0)     --->  10(0) 35(-1)
*      /    \      30            /
*     20(0)  35(0)             20(0)
*
**/

void test_nodeSearchforDeleteNode_15_10_30_20_35(void){
    //Build number tree
    initNode(&node20,NULL,NULL,0);
    initNode(&node10,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node30,&node20,&node35,0);
    initNode(&node15,&node10,&node30,1);

    //Test
    root=nodeSearchforDeleteNode(&node15,30,&deletedNode,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node15,root);
    TEST_ASSERT_EQUAL_PTR(&node30,deletedNode);
    TEST_ASSERT_EQUAL(heightDec,0);   //heightDec == 0 due to height remain same
    TEST_ASSERT_EQUAL_NODE(root,&node10,&node35,1);
    TEST_ASSERT_EQUAL_NODE(&node35,&node20,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,NULL,0);
}

/**
*      40(-1)                  40(-1)
*       /   \       delete      /   \
*     30(0)  50(0)   --->      30(1) 50(0)
*    /    \          20         \
*  20(0)  35(0)                35(0)
*
**/

void test_nodeSearchforDeleteNode_15_30_50_20_35(void){
    //Build number tree
    initNode(&node20,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node30,&node20,&node35,0);
    initNode(&node40,&node30,&node50,-1);

    //Test
    root=nodeSearchforDeleteNode(&node40,20,&deletedNode,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node40,root);
    TEST_ASSERT_EQUAL_PTR(&node20,deletedNode);
    TEST_ASSERT_EQUAL(heightDec,0);   //heightDec == 0 due to height remain same
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node50,-1);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,&node35,1);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
}

/**
*      40(-1)                   40(-1)
*       /    \      delete      /    \
*     30(0)  50(0)   --->      30(0)  50(0)
*    /    \          0       /  \
*  20(0)  35(0)          20(0)  35(0)
*
**/

void test_nodeSearchforDeleteNode_15_30_20_35(void){
    //Build number tree
    Node* delNode = NULL;
    initNode(&node20,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node30,&node20,&node35,0);
    initNode(&node40,&node30,&node50,-1);

    //Test
    root=nodeSearchforDeleteNode(&node40,0,&delNode,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node40,root);
    TEST_ASSERT_NULL(delNode);
    TEST_ASSERT_EQUAL(heightDec,0);   //heightDec == 0 due to height remain same
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node50,-1);
    TEST_ASSERT_EQUAL_NODE(&node30,&node20,&node35,0);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node35,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
}

////////////////////////////////////////////////////////////////////////////////
///rotateBalanceAndGetHeightChange//////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/**
*       40(-1)
*       /    \             no rotation
*     30(0)  50(0)   --->  but heightDec == 0
*    /    \
*  20(0)  35(0)
*
**/

void test_rotateBalanceAndGetHeightChange_40_50_30_20_35(void){
    //Build number tree
    initNode(&node20,NULL,NULL,0);
    initNode(&node50,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node30,&node20,&node35,0);
    initNode(&node40,&node30,&node50,-1);
    heightDec = 1; // set heightDec to one to check
    //Test
    root=rotateBalanceAndGetHeightChange(&node40,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node40,root);
    TEST_ASSERT_EQUAL(heightDec,0);   //heightDec == 0 due to height remain same
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node50,-1);
    TEST_ASSERT_EQUAL_NODE(&node30,&node20,&node35,0);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node35,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node50,NULL,NULL,0);
}

/**
*       40(1)
*       /    \             no rotation
*     30(0)  50(0)   --->  but heightDec == 0
*           /    \
*         45(0)  55(0)
*
**/

void test_rotateBalanceAndGetHeightChange_40_50_30_45_55(void){
    //Build number tree
    initNode(&node45,NULL,NULL,0);
    initNode(&node30,NULL,NULL,0);
    initNode(&node55,NULL,NULL,0);
    initNode(&node50,&node45,&node55,0);
    initNode(&node40,&node30,&node50,1);
    heightDec = 1; // set heightDec to one to check
    //Test
    root=rotateBalanceAndGetHeightChange(&node40,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node40,root);
    TEST_ASSERT_EQUAL(heightDec,0);   //heightDec == 0 due to height remain same
    TEST_ASSERT_EQUAL_NODE(root,&node30,&node50,1);
    TEST_ASSERT_EQUAL_NODE(&node50,&node45,&node55,0);
    TEST_ASSERT_EQUAL_NODE(&node45,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node55,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node30,NULL,NULL,0);
}

/**
*       40(-2)                 30(1)
*       /                      /    \
*     30(0)        --->     20(0)   40(-1)
*    /    \       rotate             /
*  20(0)  35(0)   left            35(0)
*
**/

void test_rotateBalanceAndGetHeightChange_40_15_30_20_35(void){
    //Build number tree
    initNode(&node20,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node30,&node20,&node35,0);
    initNode(&node40,&node30,NULL,-2);
    heightDec = 1; // set heightDec to one to check
    //Test
    root=rotateBalanceAndGetHeightChange(&node40,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node30,root);
    TEST_ASSERT_EQUAL(heightDec,0);   //heightDec == 0 due to height remain same
    TEST_ASSERT_EQUAL_NODE(root,&node20,&node40,1);
    TEST_ASSERT_EQUAL_NODE(&node40,&node35,NULL,-1);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node35,NULL,NULL,0);
}

/**
*    10(2)                      30(-1)
*       \                      /    \
*     30(0)        --->     10(1)   35(0)
*    /    \       rotate       \
*  20(0)  35(0)   right        20(0)
*
**/


void test_rotateBalanceAndGetHeightChange_10_30_20_35(void){
    //Build number tree
    initNode(&node20,NULL,NULL,0);
    initNode(&node35,NULL,NULL,0);
    initNode(&node30,&node20,&node35,0);
    initNode(&node10,NULL,&node30,2);
    heightDec = 1; // set heightDec to 1 to check
    //Test
    root=rotateBalanceAndGetHeightChange(&node10,&heightDec);
    TEST_ASSERT_EQUAL_PTR(&node30,root);
    TEST_ASSERT_EQUAL(heightDec,0);   //heightDec == 0 due to height remain same
    TEST_ASSERT_EQUAL_NODE(root,&node10,&node35,-1);
    TEST_ASSERT_EQUAL_NODE(&node10,NULL,&node20,1);
    TEST_ASSERT_EQUAL_NODE(&node20,NULL,NULL,0);
    TEST_ASSERT_EQUAL_NODE(&node35,NULL,NULL,0);
}
