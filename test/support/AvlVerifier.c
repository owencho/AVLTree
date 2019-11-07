#include "AvlVerifier.h"


int lineNo;
void verifyAvl(Node * root,int expectedNumOfElement,UNITY_LINE_TYPE lineNumber){
    uint32_t count =0;
    int height =0;
    if (!root) return ;
    lineNo = lineNumber;
    height = _verifyAvl(root, &count);
    if(expectedNumOfElement != count){

    }

}

int _verifyAvl(Node * root, uint32_t * countPtr){
    uint32_t leftCount,rightCount;
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
    if(root->bFactor >= 1 || root->bFactor <= -1){
        testReportFailure(lineNo,"balanceFactor is %d which is larger than 1 or less than -1",root->bFactor);
    }
    if(root->bFactor != rightChildHeight-leftChildHeight){
        testReportFailure(lineNo,"balanceFactor is %d which is incorrect ",root->bFactor);
    }
    *countPtr = leftCount + rightCount +1;
    if(leftChildHeight >= rightChildHeight){
        return (leftChildHeight+1) ;
    }
    else{
        return (rightChildHeight+1);
    }
}
