#include "StringCompare.h"
#include <stdio.h>
#include <string.h>
int stringCompare (StringNode *node, char * nodeAdd){
    if(strcmp(node->value ,nodeAdd)<0)
        return -1;
    else if (strcmp(node->value ,nodeAdd)>0)
        return 1;
    return 0;
}
