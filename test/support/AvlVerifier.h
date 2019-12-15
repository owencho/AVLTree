#ifndef _AVLVERIFIER_H
#define _AVLVERIFIER_H
#include "unity.h"
#include "Node.h"
#include "CustomAssert.h"
//include stdint
void verifyAvl(IntNode * root,int expectedNumOfElement, UNITY_LINE_TYPE lineNumber);
int _verifyAvl(IntNode * root, uint32_t * countPtr);

#define TEST_VERIFY_AVL_TREE(root, expectedNumOfElement) \
            verifyAvl(root,expectedNumOfElement,__LINE__)
#endif // _AVLVERIFIER_H
