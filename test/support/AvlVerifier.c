#include "AvlVerifier.h"
#include "unity.h"
#include "IntNode.h"

int lineNo;
void verifyAvl(IntNode * root,int expectedNumOfElement,UNITY_LINE_TYPE lineNumber){
    uint32_t count =0;
    int height =0;
    if (!root) return ;
    lineNo = lineNumber;
    height = _verifyAvl(root, &count);
    if(expectedNumOfElement != count){
      testReportFailure(lineNumber,"height is not the same at %d",count);
    }

}

int _verifyAvl(IntNode * root, uint32_t * countPtr){
    uint32_t leftCount=0,rightCount=0;
    int leftChildHeight=0,rightChildHeight=0;
    if(root->left != NULL){
        leftChildHeight=_verifyAvl(root->left,&leftCount);
        if(root->left->value > root->value){
            testReportFailure(lineNo,"left node (%d) is larger than the root node(%d) ",root->left->value,root->value);
        }
    }
    if (root->right != NULL){
        rightChildHeight=_verifyAvl(root->right,&rightCount);
        if(root->right->value < root->value){
            testReportFailure(lineNo,"right node (%d) is smaller than the root node(%d) ",root->right->value,root->value);
        }
    }
    *countPtr = leftCount + rightCount +1;
    if(root->bFactor > 1 || root->bFactor < -1){
        testReportFailure(lineNo,"balanceFactor in the root is %d which is larger than 1 or less than -1 on %d at index %d",root->bFactor,root->value,*countPtr);
    }
    if(root->bFactor != rightChildHeight-leftChildHeight){
        testReportFailure(lineNo,"balanceFactor in the root is %d but expected %d is incorrect on %d at index %d"
                          ,root->bFactor,rightChildHeight-leftChildHeight,root->value,*countPtr);
    }
    if(leftChildHeight >= rightChildHeight){
        return (leftChildHeight+1) ;
    }
    else{
        return (rightChildHeight+1);
    }
}
