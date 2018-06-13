//
// Created by Karolina on 05.05.2018.
//
//https://www.geeksforgeeks.org/check-if-a-given-binary-tree-is-sumtree/
//Write a function that returns true if the given Binary Tree is SumTree else false. A SumTree is a Binary Tree
//where the value of a node is equal to sum of the nodes present in its left subtree and right subtree.
//An empty tree is SumTree and sum of an empty tree can be considered as 0. A leaf node is also considered as SumTree.


#include<iostream>
using namespace std;


int sum(struct node *root)
{
    if(root == NULL)
        return 0;
    return sum(root->left) + root->data + sum(root->right);
}
int isSumTree(struct node* node)
{
    int ls, rs;

    /* If node is NULL or it's a leaf node then
       return true */
    if(node == NULL ||
       (node->left == NULL && node->right == NULL))
        return 1;

    /* Get sum of nodes in left and right subtrees */
    ls = sum(node->left);
    rs = sum(node->right);

    /* if the node and both of its children satisfy the
        property return 1 else 0*/
    if((node->data == ls + rs)&&
       isSumTree(node->left) &&
       isSumTree(node->right))

        return 1;

    return 0;
