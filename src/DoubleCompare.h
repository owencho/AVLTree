#ifndef _DOUBLECOMPARE_H
#define _DOUBLECOMPARE_H
#include "Node.h"

typedef struct DoubleNode DoubleNode;
struct DoubleNode{
    Node * left ;
    Node * right ;
    int bFactor;
    double value;
};

int doubleCompare (DoubleNode *node, double * valuePtr);

#endif // _DOUBLECOMPARE_H
