#ifndef _INTCOMPARE_H
#define _INTCOMPARE_H
#include <stdlib.h>

typedef struct IntNode IntNode;
struct IntNode{
    IntNode * left ;
    IntNode * right ;
    int bFactor;
    int value;
};
void initIntNode(IntNode * node,  IntNode * left ,IntNode * right,int balanceFactor);
int intCompare (IntNode *node, int * valuePtr);
#endif // _INTCOMPARE_H
