//
// Created by Karolina on 05.05.2018.
//
//https://www.geeksforgeeks.org/remove-all-nodes-which-lie-on-a-path-having-sum-less-than-k/
//Given a binary tree, a complete path is defined as a path from root to a leaf.
//The sum of all nodes on that path is defined as the sum of that path. Given a number K, you have to
//remove (prune the tree) all nodes which don’t lie in any path with sum>=k.
//
//Note: A node can be part of multiple paths. So we have to delete it only
//in case when all paths from it have sum less than K.


#include <iostream>
using namespace std;

struct Node
{
    int data;
    struct Node *left, *right;
};

// A utility function to create a new Binary Tree node with given data
struct Node* newNode(int data)
{
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// print the tree in LVR (Inorder traversal) way.
void print(struct Node *root)
{
    if (root != NULL)
    {
        print(root->left);
        printf("%d ",root->data);
        print(root->right);
    }
}

struct Node *prune(struct Node *root, int sum)
{
    // Base Case
    if (root == NULL) return NULL;

    // Recur for left and right subtrees
    root->left = prune(root->left, sum - root->data);
    root->right = prune(root->right, sum - root->data);

    // If we reach leaf whose data is smaller than sum,
    // we delete the leaf.  An important thing to note
    // is a non-leaf node can become leaf when its
    // chilren are deleted.
    if (root->left==NULL && root->right==NULL)
    {
        if (root->data < sum)
        {
            free(root);
            return NULL;
        }
    }

    return root;
}
int main()
{
    int k = 45;
    struct Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->left->left->left = newNode(8);
    root->left->left->right = newNode(9);
    root->left->right->left = newNode(12);
    root->right->right->left = newNode(10);
    root->right->right->left->right = newNode(11);
    root->left->left->right->left = newNode(13);
    root->left->left->right->right = newNode(14);
    root->left->left->right->right->left = newNode(15);

    printf("Tree before truncation\n");
    print(root);

    root = prune(root, k); // k is 45

    printf("\n\nTree after truncation\n");
    print(root);

    return 0;
}