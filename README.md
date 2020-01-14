# AVLTree

## 1.0 About This Project
This is AVL tree project which AVL tree is a self-balancing binary search tree that sort the node left and right . \
This AVL project separate into two parts which is **AVL Add** and **AVL Delete** . 

## 1.1 What is AVL Tree
This AVL tree technique of balancing the tree height was developed by three person which is Adelson , Velskii and Landi. \
This AVL tree will sort left sub-tree as smaller node size and right sub-tree as larger node size. \
The height difference between left part of root tree and right part of subroot tree are as known as the **balanceFactor** and the balanceFactor cannot be more than one node .
The tree is height balanced if the height between left and right part of the root tree are same or height difference between both is 1. For example,
<!-- photo of balance tree put here -->
![balanced](https://user-images.githubusercontent.com/51066670/72324141-369eaa00-36e5-11ea-8fe4-593438b71dbc.png) \
If the height difference between both is **larger than 1 , then the tree is considered as not balanced**. 
For example, \
![unbalanced](https://user-images.githubusercontent.com/51066670/72324322-99904100-36e5-11ea-8b28-cf1c8a906d22.png)
<!-- photo of non balance tree put here -->
# 2.0 Advantage of AVL tree
## 2.1 faster execution speed
As AVL trees are self-balancing binary tree , insertion (add node) , search and deletion (delete node) has lower time complexity compares to normal Binary search tree . on usual case binary search tree takes O(logn) but worst case will takes up to O(n) time to run compares to AVL tree which on any cases will always takes O(logn) time as AVL tree is always balanced.
![advantage](https://user-images.githubusercontent.com/51066670/72323767-6bf6c800-36e4-11ea-9514-a4381b37b0d8.png)
## 2.2 supports different variable and structure for the AVL tree
This AVL trees also support **different type of variable and structure** such as int , string , and any kind of structure depending on the user requirement. This AVL tree function just need to add in your own comparision function pointers for different kind of structure by using dependancy injection from one of the S.O.L.I.D principles.
![diffstruct](https://user-images.githubusercontent.com/51066670/72325212-9302c900-36e7-11ea-8250-0b2c3f71de78.png)

For example , [ShortestPath](https://github.com/owencho/ShortestPath "Shortest Path Github repo by owencho") that was also implemented this AVLTree project for finding the shortestPath by sorting with cost and name.

# 3.0 AVL Add
Avl add is one parts of the AVL tree which performs the task of insertion of nodes into the binary tree and perform rebalancing task if the tree is unbalanced after node insertion into the AVL tree.
![add](https://user-images.githubusercontent.com/51066670/72326901-0bb75480-36eb-11ea-95da-0df9e2f8ebb3.png)
## 3.1 Adding the node into Tree
Avl add will perform the task to add the node into the root by passing in the root , node to add and the function pointers for comparision.
```
Node *avlAdd(Node *root,Node * nodeAdd,Compare compare);

eg :
root=avlAdd((Node*)&node80,(Node*)&node55,(Compare)intCompareForAvlAdd);
```
This function will return the tree after executing it.
## 3.2 Rotation for Avl Add
You can refer to here <!--link to rotation-->
**Remarks** : there is no height increment when rotation is required to rotate the node. 
## 3.3 Balancing for Avl Add
### 3.3.1 For right left and left right rotation on Avl add
refer to here. <!--sauce--> \
Balancing on Avl Tree is only different on Avl Add(insertion) and Avl delete (deletion) for single rotation (rotate left and right).
### 3.3.2 For left single rotation on Avl add
When the **balanceFactor is 2 and right child node has balance Factor of 1 **
left rotation and rebalance will execute after the node has been added.

               35(2)                           50(0)
               /  \           rotate           /   \
          20(0)   50(1)       ----->       35(0)    60(1)
                 /  \          LEFT         /  \     \
             40(0) *60(1)*     rebalance   20(0) 40(0) 70(0)
                       \
                      70(0)

               25(2)                               40(0)
               /  \             rotate            /    \
           10(0)   40(1)        ----->        25(0)     60(-1)
                  /   \          LEFT          /   \       /
               30(0) *60(-1)*  rebalance    10(0) 30(0) 50(0)
                       /
                     50(0)

               20(2)                             50(0)
                  \           rotate             /   \
                 50(1)         ----->         20(0)  70(0)
                   \           LEFT
                  *70(0)*      rebalance
  
You can notice that there remark node (root->right-> right for left rotation) and it has a pattern for AVL ADD where the remarked node that determine the balanceFactor after rotation and rebalance.
Which can be simplified to the table below.
```
When the remarked node has balance factor of certain value it has a pattern 
how balance factor the root and its left and right child root will behave.

    balance factor of remarked node for left rotation Avl Add
      (-1)              (0)              (1)
      
       (0)              (0)              (0)
      /   \            /   \            /   \ 
   (0)   (-1)        (0)    (0)       (0)    (1)

```
### 3.3.3 For right single rotation Avl add
When the **balanceFactor is -2 and left child node has balance Factor of -1**
right rotation and rebalance will execute after the node has been added.
```
           30(-2)                            20(0)
         /              rotate             /      \
       20(-1)           ----->           10(0)    30(0)
     /                  RIGHT
   *10(0)*
 

             60(-2)                            40(0)
            /   \          rotate             /   \
          40(-1)  70(0)   ----->          30(-1)  60(0)
         /  \             RIGHT           /     /     \
   *30(-1)*  50(0)      rebalance       20(0)  50(0)  70(0)
       /
   20(0)


             40(-2)                            30(0)
            /   \          rotate             /     \
          30(-1) 50(0)   ----->           15(1)    40(0)
         /   \             RIGHT            \        /   \
     *15(1)* 35(0)      rebalance         20(0)     35(0) 50(0)
         \
       20(0)
```
You can notice that there remark node (root->left-> left for right rotation) and it has a pattern for AVL ADD where the remarked node that determine the balanceFactor after rotation and rebalance.
Which can be simplified to the table below.
```
When the remarked node has balance factor of certain value it has a pattern 
how balance factor the root and its left and right child root will behave.

    balance factor of remarked node for right rotation Avl Add
      (-1)              (0)              (1)
      
       (0)              (0)              (0)
      /   \            /   \            /   \ 
   (-1)   (0)        (0)    (0)       (1)    (0)

```
# 4.0 AVL Delete
Avl add is another part of the AVL tree which performs the task of removal (delete) of nodes from the binary tree and perform rebalancing task if the tree is unbalanced after node was deleted from the AVL tree.
## 4.1 removing the node into Tree
Avl add will perform the task to remove the node from the root by passing value to delete the selected node.
```
Node *avlDelete(Node ** root,void * nodeDelete,Compare compare);

eg :
deletedNode=avlDelete(&root,(void*)&deleteValue,(Compare)intCompareForAvlDelete);
```
## 4.2 Rotation for Avl Delete
You can refer to here. <!--link to rotation--> \
**Remarks** : there is no height decrement when rotation is required to rotate the node for balancing. 
### 3.3.2 For left single rotation on Avl Delete
When the **balanceFactor is 2 and root right node has balance Factor ==1 and 0 **
left rotation and rebalance will execute after the node has been deleted .
```
When root right node has balance factor of 1 

              35(2)                           50(0)
              /  \           rotate           /   \
         20(0)   50(1)       ----->       35(0)    60(1)
                /  \          LEFT         /  \     \
            40(0) 60(1)     rebalance   20(0) 40(0) 70(0)
                      \
                     70(0)


               25(2)                             40(0)
               /  \            rotate            /   \
           10(0)   40(1)       ----->        25(0)   50(1)
                   /  \         LEFT          /  \     \
                30(0) 60(-1)    rebalance    10(0) 30(0) 60(0)
                       /
                     50(0)


         20(2)                           50(0)
          \           rotate             /   \
           50(1)       ----->         20(0)  70(0)
            \           LEFT
             70(0)      rebalance

When root right node has balance factor of 0 

        30(2)                                 70(-1)
       /   \              rotate              /   \
     5(0)   70(0)            ----->         30(1)  75(1)
           /    \           LEFT            /   \     \
       65(-1)  75(1)                    5(0)  65(-1)  80(0)
          /       \                             /
       60(0)    80(0)                        60(0)


      30(2)                                70(-1)
        \              rotate             /   \
        70(0)            ----->         30(1)  75(0)
       /    \           LEFT              \
     65(0) 75(0)                         65(0)

      
```

