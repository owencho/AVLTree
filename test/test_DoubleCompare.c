#include "unity.h"
#include "DoubleCompare.h"
#include "DoubleNode.h"
#include "Compare.h"
#include "Node.h"
DoubleNode node1, node5, node10, node15,node20,node25,node30,node35,node40,node45,node50,node55;
DoubleNode node60,node65,node70,node75,node80,node85,node90,node95,node99;
void setUp(void){
    node1.value =1.123;   node5.value =5;   node15.value =15;
    node20.value =20; node25.value =25; node30.value =30;
    node35.value =35; node40.value =40; node45.value =45;
    node50.value =50; node55.value =55; node60.value =60;
    node65.value =65; node70.value =70; node75.value =75;
    node80.value =80; node85.value =85; node90.value =90;
    node95.value =95; node99.value =99; node10.value =10;
}
void tearDown(void){}
// doubleCompare return 1 when when root > nodeAdd
// doubleCompare return -1 when when root < nodeAdd
// doubleCompare return 0 when when root == nodeAdd
void test_DoubleCompare(void){
    Compare compare = (Compare)doubleCompare;
    double i = 1.123;
    TEST_ASSERT_EQUAL(0,(compare((Node*)&node1,(void *)&i)));
}

void test_DoubleCompare_smaller_root_return_neg1(void){
    Compare compare = (Compare)doubleCompare;
    double i = 1.123;
    TEST_ASSERT_EQUAL(1,(compare((Node*)&node5,(void *)&i)));
}

void test_DoubleCompare_larger_root_return_1(void){
    Compare compare = (Compare)doubleCompare;
    double i = 12.123;
    TEST_ASSERT_EQUAL(-1,(compare((Node*)&node5,(void *)&i)));
}
