#ifndef _DOUBLENODE_H
#define _DOUBLENODE_H

typedef struct DoubleNode DoubleNode;
struct DoubleNode{
    DoubleNode * left ;
    DoubleNode * right ;
    int bFactor;
    double value;
};
#endif // _DOUBLENODE_H
