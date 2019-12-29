#ifndef _STRINGNODE_H
#define _STRINGNODE_H

typedef struct StringNode StringNode;
struct StringNode{
    StringNode * left ;
    StringNode * right ;
    int bFactor;
    char* value;
};

#endif // _STRINGNODE_H
