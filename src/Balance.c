#include "Balance.h"

Node* balanceForDoubleRotate(Node* root , int bFactor){
      if(root == NULL)
          return root;
      root->left->bFactor = (-1-(bFactor-1)>>1)*(bFactor&1);
      root->right->bFactor = (0-(bFactor-1)>>1)*(bFactor&1);
      root->bFactor =0;
      return root;
}
