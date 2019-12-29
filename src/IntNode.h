#ifndef _INTNODE_H
#define _INTNODE_H

typedef struct IntNode IntNode;
struct IntNode{
    IntNode * left ;
    IntNode * right ;
    int bFactor;
    int value;
};
#endif // _INTNODE_H
