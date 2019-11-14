#ifndef _NODE_H
#define _NODE_H
#include <stdlib.h>
typedef struct Node Node ;

struct Node{
    Node * left ;
    Node * right ;
    int bFactor;
    int value;
};
Node * createNode(int value,  Node * left ,Node * right,int balanceFactor);
void initNode(Node * node,  Node * left ,Node * right,int balanceFactor);

#define freeNode(node)                                      \
                          do{if(node) free(node);} while(0)
#endif // _NODE_H
