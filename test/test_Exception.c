#include "unity.h"
#include "AvlError.h"
#include "Exception.h"
#include "AvlError.h"
#include "CException.h"

CEXCEPTION_T ex;

void setUp(void){}
void tearDown(void){}


void test_throwException(void){

    Try{
        throwException(ERR_SAME_NODE,"test throw exeception");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_SAME_NODE, ex->errorCode);
    }
}

void test_dumpException(void){
    Try{
        throwException(ERR_SAME_NODE,"test throw exeception");
    }Catch(ex) {
        dumpException(ex);
        TEST_ASSERT_EQUAL(ERR_SAME_NODE, ex->errorCode);
    }
}
