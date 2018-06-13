//
// Created by Karolina on 08.05.2018.
//
//Dla drzewa BST:

#include <iostream>
using namespace std;

// A Binary Tree Node
struct Node
{
    struct Node *left, *right,*parent;
    int value;
};
//złożonosc algo to wysokość drzewa O(h)
Node *lca(Node* root, int n1, int n2)
{
    while (root != NULL)
    {
        if (root->value > n1 && root->value > n2)
            root = root->left;

        else if (root->value < n1 && root->value < n2)
            root = root->right;

        else break;
    }
    return root;
}
int distancetoroot(Node *root,Node *p){
    if(root==NULL) return -1;
    int distance=0;
    Node *tmp=p;
    while(tmp->parent!=NULL || tmp->parent==root) {
        tmp = tmp->parent;
        distance++;
    }
    return distance;
}
Node * findNode(Node * root, int value){
    if(root == NULL) return NULL;
    if(root->value == value) return root;
    else if(value < root->value) return findNode(root->left,value);
    else return findNode(root->right,value);
}

int distance(Node* root,int a, int b){
    Node *A = findNode(root,a);
    Node *B= findNode(root,b);
    return distancetoroot(root,A) + distancetoroot(root,B)-2*distancetoroot(root,lca(root,a,b));
}


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
        if(root->left) printBST(root->left);
        cout << root->value << " ";
        if(root->right) printBST(root->right);
    }
}
int main() {
    Node *tree = NULL;
    addNode(tree, 15);
    addNode(tree, 11);
    addNode(tree, 20);
    addNode(tree, 7);
    addNode(tree, 12);
    addNode(tree, 19);
    addNode(tree, 30);
    addNode(tree, 8);
   
    printBST(tree);
    cout<<endl;
    cout<<distance(tree,8,11)<<endl;
    cout<<distance(tree,7,30)<<endl;
    cout<<distance(tree,15,30)<<endl;

}
