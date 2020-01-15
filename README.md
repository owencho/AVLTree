# AVLTree

## 1.0 About This Project
This is AVL tree project which AVL tree is a self-balancing binary search tree that sort the node left and right . \
This AVL project separate into two parts which is **AVL Add** and **AVL Delete** . 

## 1.1 What is AVL Tree
This AVL tree technique of balancing the tree height was developed by three person which is Adelson , Velskii and Landi. \
This AVL tree will sort left sub-tree as smaller node size and right sub-tree as larger node size. \
The height difference between left part of root tree and right part of subroot tree are as known as the **balanceFactor** and the balanceFactor cannot be more than one node .
The tree is height balanced if the height between left and right part of the root tree are same or height difference between both is 1. For example,
![balanced](https://user-images.githubusercontent.com/51066670/72324141-369eaa00-36e5-11ea-8fe4-593438b71dbc.png) \
If the height difference between both is **larger than 1 , then the tree is considered as not balanced**. 
For example, \
![unbalanced](https://user-images.githubusercontent.com/51066670/72324322-99904100-36e5-11ea-8b28-cf1c8a906d22.png)
# 2.0 Advantage of AVL tree
## 2.1 Faster execution speed
As AVL trees are self-balancing binary tree , insertion (add node) , search and deletion (delete node) has lower time complexity compares to normal Binary search tree . on usual case binary search tree takes O(logn) but worst case will takes up to O(n) time to run compares to AVL tree which on any cases will always takes O(logn) time as AVL tree is always balanced.
![advantage](https://user-images.githubusercontent.com/51066670/72323767-6bf6c800-36e4-11ea-9514-a4381b37b0d8.png)
## 2.2 Supports different variable and structure for the AVL tree
This AVL trees also support **different type of variable and structure** such as int , string , and any kind of structure depending on the user requirement. This AVL tree function just need to add in your own comparision function pointers for different kind of structure by using dependancy injection from one of the S.O.L.I.D principles.
![diffstruct](https://user-images.githubusercontent.com/51066670/72325212-9302c900-36e7-11ea-8250-0b2c3f71de78.png)

For example , [ShortestPath](https://github.com/owencho/ShortestPath "Shortest Path Github repo by owencho") that was also implemented this AVLTree project for finding the shortestPath by sorting with cost and name.

# 3.0 AVL Add
Avl add is one parts of the AVL tree which performs the task of insertion of nodes into the binary tree and perform rebalancing task if the tree is unbalanced after node insertion into the AVL tree. AVL add function will compare using the function pointer to find where the node should be added into the tree.
![add](https://user-images.githubusercontent.com/51066670/72413011-c4dc6400-37a9-11ea-9697-b799cbe0b423.png)
## 3.1 Adding the node into Tree
Avl add will perform the task to add the node into the root by passing in the root , node to add and the function pointers for comparision.
```
Node *avlAdd(Node *root,Node * nodeAdd,Compare compare);

eg :
root=avlAdd((Node*)&node80,(Node*)&node55,(Compare)intCompareForAvlAdd);
```
This function will return the tree after executing it.
## 3.2 Rotation for Avl Add
You can refer to [here](https://github.com/owencho/AVLTree/blob/master/README.md#50-rotation") . 

## 3.3 Balancing for Avl Add
### 3.3.1 For right left and left right rotation on Avl add
refer [here](https://github.com/owencho/AVLTree/blob/master/README.md#50-balancing-for-double-rotation "balancing for double rotation"). \
Balancing on Avl Tree is only different on Avl Add(insertion) and Avl delete (deletion) for single rotation (rotate left and right).
### 3.3.2 For left single rotation on Avl add
When the **balanceFactor is 2 and right child node has balance Factor of 1**
left rotation and rebalance will execute after the node has been added.

               35(2)                           50(0)
               /  \            rotate          /   \
          20(0)   50(1)        ----->       35(0)    60(1)
                 /  \          LEFT         /  \     \
             40(0) *60(1)*     rebalance   20(0) 40(0) 70(0)
                       \
                      70(0)

               25(2)                               40(0)
               /  \             rotate            /    \
           10(0)   40(1)        ----->        25(0)     60(-1)
                  /   \         LEFT           /   \       /
               30(0) *60(-1)*   rebalance    10(0) 30(0) 50(0)
                       /
                     50(0)

               20(2)                             50(0)
                  \            rotate            /   \
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
Avl Delete is another part of the AVL tree project which performs the task of removal (delete) of nodes from the binary tree and perform rebalancing task if the tree is unbalanced after node was deleted from the AVL tree.
AVL Delete function will compare using the function pointer to find where the node should be delete inside the tree and find the replacer to replace the deleted node.
![delete](https://user-images.githubusercontent.com/51066670/72413010-c443cd80-37a9-11ea-9230-c5e031170044.png)
## 4.1 Removing the node into Tree
Avl Delete will perform the task to remove the node from the root by passing value to delete the selected node.
```
Node *avlDelete(Node ** root,void * nodeDelete,Compare compare);

eg :
deletedNode=avlDelete(&root,(void*)&deleteValue,(Compare)intCompareForAvlDelete);
```
## 4.2 Rotation for Avl Delete
You can refer to [here](https://github.com/owencho/AVLTree/blob/master/README.md#50-rotation") .
## 4.3 Balancing for Avl Delete
### 4.3.1 For right left and left right rotation on Avl delete
You can refer to [here](https://github.com/owencho/AVLTree/blob/master/README.md#50-balancing-for-double-rotation "balancing for double rotation") .\
Balancing on Avl Tree is only different on Avl Add(insertion) and Avl delete (deletion) for single rotation (rotate left and right).
### 4.3.2 For left single rotation on Avl Delete
When the **balanceFactor is 2 and root right node has balance Factor of 1 and 0**
left rotation and rebalance will execute after the node has been deleted .
```
When root right node has balance factor of 1 

              35(2)                           50(0)
              /  \            rotate          /   \
         20(0)   50(1)        ----->      35(0)    60(1)
                /  \          LEFT         /  \     \
            40(0) *60(1)*     rebalance   20(0) 40(0) 70(0)
                      \
                     70(0)


               25(2)                                40(0)
               /  \               rotate            /    \
           10(0)   40(1)          ----->        25(0)     60(-1)
                   /  \           LEFT           /  \       /
                30(0) *60(-1)*    rebalance    10(0) 30(0) 50(0)
                       /
                     50(0)


         20(2)                             50(0)
          \             rotate             /   \
           50(1)        ----->          20(0)  70(0)
            \           LEFT
           *70(0)*      rebalance
```             
When the remarked node has balance factor of certain value it has a pattern 
how balance factor the root and its left and right child root will behave.
```
    balance factor of remarked node for left rotation Avl Delete 
    when balance factor root right is 1 
      (-1)              (0)              (1)
      
       (0)               (0)              (0)
      /   \             /   \            /   \ 
   (0)    (-1)        (0)    (0)       (0)    (1)

``` 
When root right node has balance factor of 0 
```

        30(2)                                 70(-1)
       /   \              rotate              /   \
     5(0)   70(0)         ----->           30(1)  75(1)
           /    \         LEFT             /   \     \
       65(-1)  75(1)      rebalance      5(0)  65(-1)  80(0)
          /       \                             /
       60(0)    80(0)                        60(0)


        30(2)                                   70(-1)
       /   \              rotate              /       \
     5(0)   70(0)         ----->          30(1)     80(-1)
           /    \         LEFT            /   \       /
       65(-1)  80(-1)     rebalance    5(0)  65(-1) 75(0)
          /      /                              /
       60(0)   75(0)                        60(0)


      30(2)                                70(-1)
        \               rotate             /   \
        70(0)           ----->          30(1)  75(0)
       /    \           LEFT              \
     65(0) 75(0)        rebalance         65(0)

     
    balance factor of remarked node for left rotation Avl Delete 
    when balance factor root right is 0
      (-1)                (0)              (1)
      
       (-1)               (-1)              (-1)
      /    \             /   \             /   \ 
   (1)     (1)         (1)    (-1)       (1)    (0)

``` 
### 4.3.3 For right single rotation Avl delete
When the **balanceFactor is -2 and left child node has balance Factor of -1 or 0**
right rotation and rebalance for AVL delete will execute after the node has been added.
```
           30(-2)                            20(0)
         /              rotate             /      \
       20(-1)           ----->           10(0)    30(0)
     /                  RIGHT
   *10(0)*
 

             60(-2)                            40(0)
            /   \         rotate              /   \
          40(-1)  70(0)   ----->           30(-1)  60(0)
         /  \             RIGHT            /     /     \
   *30(-1)*  50(0)        rebalance       20(0)  50(0)  70(0)
       /
   20(0)


             40(-2)                            30(0)
            /   \        rotate               /     \
          30(-1) 50(0)   ----->            15(1)    40(0)
         /   \           RIGHT              \        /   \
     *15(1)* 35(0)       rebalance         20(0)     35(0) 50(0)
         \
       20(0)
```             
When the remarked node has balance factor of certain value it has a pattern 
how balance factor the root and its left and right child root will behave.
```
    balance factor of remarked node for right rotation Avl Delete 
    when balance factor root left is -1 
      (-1)              (0)              (1)
      
       (0)               (0)              (0)
      /   \             /   \            /   \ 
   (-1)    (0)        (0)    (0)       (1)    (0)

``` 
When root left node has balance factor of 0 
```
        60(-2)                              40(1)
          /              rotate             /   \
       40(0)            ----->         30(0)   60(-1)
      /     \           RIGHT                     /
    *30(0)*  55(0)                              55(0)


       85(-2)                                70(1)
        /   \              rotate             /   \
     70(0)   90(0)         ----->         65(-1)  85(-1)
      /    \                 RIGHT          /      /    \
  *65(-1)* 75(1)                         60(0)  75(1)  90(0)
    /       \                                      \
   60(0)    80(0)                                  80(0)


      85(-2)                                  70(1)
        /   \              rotate             /   \
     70(0)   90(0)         ----->         60(1)  85(-1)
      /    \                 RIGHT          \      /    \
  *60(1)* 75(1)                            65(0)  75(1)  90(0)
     \       \                                      \
   65(0)    80(0)                                  80(0)

    balance factor of remarked node for right rotation Avl Delete 
    when balance factor root left is 0 
      (-1)              (0)              (1)
      
       (1)               (0)               (1)
      /   \             /   \             /   \ 
   (-1)    (-1)        (0)   (-1)       (1)    (-1)

```
## 4.3 Finding replacer after the node deleted
This AVL will automatically find the node to replace when a node got deleted. It will select the node that is located at the smallest node starts from its right child node to replace the original node.

There's 4 scenario where it could happened when finding the replacer
### 4.3.1 When there is no left node on the right of deleted node
The right of the deleted node will replace the original node as left of (deletedNode ->right ) is empty.
![replacement1](https://user-images.githubusercontent.com/51066670/72412500-6c589700-37a8-11ea-8fe4-946581145a92.png)
### 4.3.2 When the deletedNode does not have right child node 
The left of the deleted node will replace the original node as right child of deletedNode is empty.
![replacement2](https://user-images.githubusercontent.com/51066670/72412473-5c40b780-37a8-11ea-81e3-d1f059b595f3.png)
### 4.3.3 When there is left node on the right of deleted node
The smallest node from the right child node of deleted node will replace the deleted node
![replacement3](https://user-images.githubusercontent.com/51066670/72412474-5c40b780-37a8-11ea-8b47-110d2ce44016.png)
### 4.3.4 When the smallest node on the right of deleted node has child node
The smallest node from the right child node of deleted node will replace the deleted node and its child will remain at same location as it replace the smallest node 
![replacement4](https://user-images.githubusercontent.com/51066670/72412470-5ba82100-37a8-11ea-8b51-c530f271f53e.png)

# 5.0 Rotation
There's 4 type of rotation for AVL tree which is rotate left , rotate right , rotate right then left and rotate left then right.

## 5.1 Left Rotation

         20                           50
          \        Rotate           /   \
           50      ----->          20    70
            \      LEFT
             70

## 5.2 Right Rotation
```
        30                                  20
        /              Rotate              /   \
      20               ----->            10     30
    /                  RIGHT
  10
```  
## 5.3 Right Left Rotation

       10                    10
        \       Rotate        \         Rotate        20
        30      ----->         20        ---->       /  \
       /        RIGHT           \        LEFT      10    30
      20                         30
      
## 5.4 Left Right Rotation

        80                         80
       /           Rotate          /      Rotate       50
     20            ----->        50       ---->       /  \
      \            LEFT         /         RIGHT     20    80
       50                     20

# 5.0 Balancing for double rotation
## 5.1 Left right rotation balancing 
When the **balanceFactor is -2 and left child node has balance Factor of 1**
```
      80(-2)                             60(0)
     /     \          Rotate           /       \
    30(1)  90(0)      ---->         30(-1)   80(0)
   /     \            LEFTRIGHT     /        /    \
  10(0)  *60(1)*                  10(0)     70(0)  90(0)
             \
            70(0)


      80(-2)                             60(0)
     /     \          Rotate           /       \
    30(1)  90(0)      ---->         30(0)    80(1)
   /     \            LEFTRIGHT     /    \       \
  10(0)  *60(-1)*                     10(0) 55(0)  90(0)
           /
        55(0)


      60(-2)                            55(0)
       /           rotate             /      \
   50(1)           ----->           50(0)    60(0)
     \           LEFT RIGHT
    *55(0)*

    balance factor of remarked node for left right rotation 
      (-1)              (0)              (1)
      
       (0)               (0)               (0)
      /   \             /   \             /   \ 
   (-1)    (0)        (0)   (0)        (0)    (1)
```   
## 5.2 Right left rotation balancing 
When the **balanceFactor is 2 and right child node has balance Factor of -1**
```
    50(2)                               55(0)
       \           rotate             /      \
     60(-1)         ----->         50(0)    60(0)
     /           RIGHT LEFT
    *55(0)*
 
        25(2)                                    35(0)
       /   \                 rotate             /     \
     20(0)  40(-1)           ----->         25(0)     40(1)
            /   \            RIGHT          /   \        \
       *35(-1)*  50(0)       LEFT        20(0) 30(0)   50(0)
          /
       30(0)

        25(2)                                   30(0)
       /   \                rotate             /     \
    20(0)  40(-1)           ----->         25(-1)   40(0)
            /   \            RIGHT         /         /  \
       *30(1)*  50(0)        LEFT       20(0)     35(0) 50(0)
                  \
                 35(0)
                 
    balance factor of remarked node for right left rotation 
      (-1)              (0)              (1)
      
       (0)               (0)               (0)
      /   \             /   \             /   \ 
   (0)    (1)        (0)   (0)         (-1)    (0)
```   
# 6.0 Node comparision
The node can be compared by inserting the function pointer that compares for the node to go left and right.
The function will take in two node (one from root and one to be added) for comparision for AVL add and the function will take in one node and one variable with value (to delete from node) to compare for Avl Delete.

For same value it will return 0 \
For node to be added > root it will return -1 \
For node to be added < root it will return 1  

# 7.0 Source file
- For Source Code details [click here](https://github.com/owencho/AVLTree/tree/master/src)
- For Test Code details [click here](https://github.com/owencho/AVLTree/tree/master/test)
