# AVLTree

## 1.0 About This Project
This is AVL tree project which AVL tree is a self-balancing binary search tree that sort the node left and right . \
This AVL project separate into two parts which is **AVL Add** and **AVL Delete** . 

## 1.1 What is AVL Tree
This AVL tree technique of balancing the tree height was developed by three person which is Adelson , Velskii and Landi. \
This AVL tree will sort left sub-tree as smaller node size and right sub-tree as larger node size. \
The height difference between left part of root tree and right part of subroot tree are as known as the **balanceFactor** and the balanceFactor cannot be more than one node .\
The tree is height balanced if the height between left and right part of the root tree are same or height difference between both  
is 1 . For example the picture of balanced tree below .
<!-- photo of balance tree put here -->
![balanced](https://user-images.githubusercontent.com/51066670/72324141-369eaa00-36e5-11ea-8fe4-593438b71dbc.png) \
If the height difference between both is **larger than 1 , then the tree is considered as not balanced**. For example the picture of unbalanced tree below . \
![unbalanced](https://user-images.githubusercontent.com/51066670/72324322-99904100-36e5-11ea-8b28-cf1c8a906d22.png)
<!-- photo of non balance tree put here -->
# 2.0 Advantage of AVL tree
## 2.1 faster execution speed
As AVL trees are self-balancing binary tree , insertion (add node) , search and deletion (delete node) has lower time complexity compares to normal Binary search tree . on usual case binary search tree takes O(logn) but worst case will takes up to O(n) time to run compares to AVL tree which on any cases will always takes O(logn) time as AVL tree is always balanced.
![advantage](https://user-images.githubusercontent.com/51066670/72323767-6bf6c800-36e4-11ea-9514-a4381b37b0d8.png)
## 2.2 supports different variable and structure for the AVL tree
This AVL trees also support **different type of variable and structure** such as int , string , and any kind of structure that user wants. This AVL tree function just need to add in your own comparision function pointers for different kind of structure by using dependancy injection from one of the S.O.L.I.D principles.
![diffstruct](https://user-images.githubusercontent.com/51066670/72325212-9302c900-36e7-11ea-8250-0b2c3f71de78.png)

For example , [ShortestPath](https://github.com/owencho/ShortestPath "Shortest Path Github repo by owencho") that was also implemented this AVLTree project for finding the shortestPath by sorting with cost and name.


