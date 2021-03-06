#ifndef _NODE_H
#define _NODE_H
#include <stdlib.h>
typedef struct Node Node ;

struct Node{
    Node * left ;
    Node * right ;
    int bFactor;
    char value[0];
};
void freeAllNodesInTree(Node *root);

#define freeNode(node)                                      \
                          do{if(node) free(node);} while(0)
#endif // _NODE_H
