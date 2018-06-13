//
// Created by Karolina on 05.05.2018.
//
//https://www.geeksforgeeks.org/find-distance-between-two-nodes-of-a-binary-tree/
//Find the distance between two keys in a binary tree, no parent pointers are given.
//Distance between two nodes is the minimum number of edges to be traversed to reach one node from other.

//znaleść wspólnego potomka, i zwórcić sume path_to_root dla obu nodów
//Dist(n1, n2) = Dist(root, n1) + Dist(root, n2) - 2*Dist(root, lca)
//'n1' and 'n2' are the two given keys
//'root' is root of given Binary Tree.
//'lca' is lowest common ancestor of n1 and n2
//        Dist(n1, n2) is the distance between n1 and n2


#include <iostream>
using namespace std;

// A Binary Tree Node
struct Node
{
    struct Node *left, *right;
    int key;
};

// Utility function to create a new tree Node
Node* newNode(int key)
{
    Node *temp = new Node;
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}
Node* LCA(Node * root, int n1,int n2)
{
    // Your code here
    if (root == NULL)
        return root;
    if (root->key == n1 || root->key == n2)
        return root;

    Node* left = LCA(root->left, n1, n2);
    Node* right = LCA(root->right, n1, n2);

    if (left != NULL && right != NULL)
        return root;
    if (left != NULL)
        return LCA(root->left, n1, n2);

    return LCA(root->right, n1, n2);
}

int findLevel(Node *root, int k, int level)
{
    if(root == NULL) return -1;
    if(root->key == k) return level;

    int left = findLevel(root->left, k, level+1);
    if (left == -1)
        return findLevel(root->right, k, level+1);
    return left;
}

int findDistance(Node* root, int a, int b)
{
    // Your code here
    Node* lca = LCA(root, a , b);
    cout<<endl;
    cout<<" "<< lca->key<<" "<<endl;
    int d1 = findLevel(lca, a, 0);
    int d2 = findLevel(lca, b, 0);

    return d1 + d2;
}
//alternatywa znajdowania wspólnego przodka
//uzupełniamy struckure o informacje odnośnie odległosci każdego noda do głownego korzenia


//Dla drzewa BST:
Node *lca(Node* root, int n1, int n2)
{
    while (root != NULL)
    {
        // If both n1 and n2 are smaller than root, then LCA lies in left
        if (root->key > n1 && root->key > n2)
            root = root->left;

            // If both n1 and n2 are greater than root, then LCA lies in right
        else if (root->key < n1 && root->key < n2)
            root = root->right;

        else break;
    }
    return root;
}



// Driver program to test above functions
int main()
{
    // Let us create binary tree given in
    // the above example
    Node * root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->right->left->right = newNode(8);
    cout << "Dist(4, 5) = " << findDistance(root, 4, 5);
    cout << "\nDist(4, 6) = " << findDistance(root, 4, 6);
    cout << "\nDist(3, 4) = " << findDistance(root, 3, 4);
    cout << "\nDist(2, 4) = " << findDistance(root, 2, 4);
    cout << "\nDist(8, 5) = " << findDistance(root, 8, 5);
    return 0;
}