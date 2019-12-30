#include "StringCompare.h"
#include <stdio.h>
#include <string.h>
int stringCompareForAvlAdd (StringNode *node, StringNode *nodeAdd){
    if(strcmp(node->str ,nodeAdd->str)<0)
        return -1;
    else if (strcmp(node->str ,nodeAdd->str)>0)
        return 1;
    return 0;
}
int stringCompareForAvlDelete (StringNode *node, char * nodeDelete){
    if(strcmp(node->str ,nodeDelete)<0)
        return -1;
    else if (strcmp(node->str ,nodeDelete)>0)
        return 1;
    return 0;
}
