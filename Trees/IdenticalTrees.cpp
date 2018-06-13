//
// Created by Karolina on 05.05.2018.
//

//https://www.geeksforgeeks.org/write-c-code-to-determine-if-two-trees-are-identical/
//        Two trees are identical when they have same data and arrangement of data is also same.
//
//To identify if two trees are identical, we need to traverse both trees simultaneously,
//and while traversing we need to compare data and children of the trees.
//zł: rozmiar drzewa O(n)
#include<iostream>
using namespace std;

struct Node{
    Node * parent;
    Node * left;
    Node * right;
    int value;
};

struct Node* newNode(int data)
{
    struct Node* Node = (struct Node*)
            malloc(sizeof(struct Node));
    Node->value  = data;
    Node->left  = NULL;
    Node->right = NULL;

    return(Node);
}
int identicalTrees(Node* a, Node* b)
{
    /*1. both empty */
    if (a==NULL && b==NULL)
        return 1;

    /* 2. both non-empty -> compare them */
    if (a!=NULL && b!=NULL)
    {
        return
                (
                        a->value == b->value &&
                        identicalTrees(a->left, b->left) &&
                        identicalTrees(a->right, b->right)
                );
    }

    /* 3. one empty, one not -> false */
    return 0;

}

int main()
{
    struct Node *root1 = newNode(1);
    struct Node *root2 = newNode(1);
    root1->left = newNode(2);
    root1->right = newNode(3);
    root1->left->left  = newNode(4);
    root1->left->right = newNode(5);

    root2->left = newNode(2);
    root2->right = newNode(3);
    root2->left->left = newNode(4);
    root2->left->right = newNode(5);

    if(identicalTrees(root1, root2))
        printf("Both tree are identical.");
    else
        printf("Trees are not identical.");


    return 0;
}