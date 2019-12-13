#ifndef CustomAssert_H
#define CustomAssert_H
#include "unity.h"
#include "Node.h"
#include "IntNode.h"

void assertEqualIntNode (const IntNode * actualNode,
                       const IntNode * leftNode,
                       const IntNode * rightNode,
                       const int balanceFactor,
                      const UNITY_LINE_TYPE lineNumber);

void testReportFailure (const UNITY_LINE_TYPE lineNumber,char* message ,...);


#define TEST_ASSERT_EQUAL_INT_NODE(actualNode,leftNode,rightNode,balanceFactor)        \
                      assertEqualIntNode(actualNode,leftNode,rightNode,balanceFactor,__LINE__)



#endif // CustomAssert_H
