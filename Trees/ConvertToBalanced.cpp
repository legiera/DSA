//
// Created by Karolina on 05.05.2018.
//

//https://www.geeksforgeeks.org/convert-normal-bst-balanced-bst/
// Given a BST (Binary Search Tree) that may be unbalanced, convert it into a balanced BST that has minimum possible height.
#include <iostream>
using namespace std;
struct Node{
    Node *right,*left,*parent;
    int value;
};


void addNode(Node *& root, int value){
    Node * tmp = new Node;
    tmp->value = value;
    tmp->left = tmp->right = tmp->parent = NULL;
    if(root == NULL) root = tmp;
    else{
        Node * p = root; // element do przeszukiwania
        Node * q = NULL; // previous dla parenta
        while(p != NULL){
            if(p->value < tmp->value){
                q = p;
                p = p->right;
            }
            else{
                q = p;
                p = p->left;
            }
        }
        if(q->value < value) q->right = tmp;
        else q->left = tmp;
        tmp->parent = q;
    }
}
void printBST(Node * root){
    if(root != NULL){
        cout << root->value << " ";

        if(root->left) printBST(root->left);
        //cout<<endl;
        if(root->right) printBST(root->right);
        //  cout<<"      ";
    }
}
Node* newNode(int data)
{
    Node* node = new Node;
    node->value = data;
    node->left = node->right = NULL;
    return (node);
}

Node* buildTreeUtil(int tab[], int start,int end){
// base case
    if (start > end)
    return NULL;

/* Get the middle element and make it root */
    int mid = (start + end)/2;
    Node *root = newNode(tab[mid]);
  //  cout<<"||||||||||"<<endl;
 //   printBST(root);

/* Using index in Inorder traversal, construct
   left and right subtress */
    root->left  = buildTreeUtil(tab, start, mid-1);
    root->right = buildTreeUtil(tab, mid+1, end);

   // printBST(root);
    return root;
}

void storeBSTNodes(Node* root, int tab[],int &i)
{
    // Base case
    if (root==NULL)
        return;
    storeBSTNodes(root->left, tab,i);
    tab[i++]=root->value;
    storeBSTNodes(root->right, tab,i);
}
const int n=5;
Node* buildTree(Node* root)
{
    // Store nodes of given BST in sorted order
    int tab[n];
    int i=0;
    storeBSTNodes(root, tab,i);
   // for(int i=0;i<n;i++) cout<<tab[i]<<endl;
    // Constucts BST from nodes[]
    return buildTreeUtil(tab, 0, n-1);
}



int main(){
    Node * tree = NULL;
    addNode(tree,15);
    addNode(tree,11);
    addNode(tree,20);
    addNode(tree,7);
    addNode(tree,12);
    addNode(tree,19);
    addNode(tree,30);
    addNode(tree,8);
  //  printBST(tree);
    cout<<endl;

   // buildTree(tree);
  //  printBST(tree);
    cout<<endl;
    Node* root = newNode(10);
    root->left = newNode(8);
    root->left->left = newNode(7);
    root->left->left->left = newNode(6);
    root->left->left->left->left = newNode(5);
    printBST(root);
    cout<<endl;
   printBST( buildTree(root));
    cout<<endl;

}