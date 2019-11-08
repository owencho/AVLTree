#ifndef CustomAssert_H
#define CustomAssert_H
#include "unity.h"
#include "Node.h"

void assertEqualNode (const Node * actualNode,
                       const Node * leftNode,
                       const Node * rightNode,
                       const int balanceFactor,
                      const UNITY_LINE_TYPE lineNumber);

void testReportFailure (const UNITY_LINE_TYPE lineNumber,char* message ,...);


#define TEST_ASSERT_EQUAL_NODE(actualNode,leftNode,rightNode,balanceFactor)        \
                      assertEqualNode(actualNode,leftNode,rightNode,balanceFactor,__LINE__)



#endif // CustomAssert_H
