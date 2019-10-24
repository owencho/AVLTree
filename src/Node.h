#ifndef _NODE_H
#define _NODE_H
#include <stdlib.h>
typedef struct Node Node ;

struct Node{
    Node * left ;
    Node * right ;
    int bfactor;
    int value;
};

Node * createNode(int value,  Node * left ,Node * right);

#define freeNode(node)                                      \
                          do{if(node) free(node);}while(0)
#endif // _NODE_H
