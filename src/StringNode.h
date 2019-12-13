#ifndef _STRINGNODE_H
#define _STRINGNODE_H

typedef struct StringNode StringNode;
struct StringNode{
    StringNode * left ;
    StringNode * right ;
    int bFactor;
    char* value;
};

void initStringNode(StringNode * node,  StringNode * left ,StringNode * right,int balanceFactor);
#endif // _STRINGNODE_H
