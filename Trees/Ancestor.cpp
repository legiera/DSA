//
// Created by Karolina on 05.05.2018.
//
//https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/
//Given a binary tree (not a binary search tree) and two values say n1 and n2,
//write a program to find the least common ancestor.
#include <iostream>
using namespace std;
// robie to dla BST

struct BSTnode{
    BSTnode * parent;
    BSTnode * left;
    BSTnode * right;
    int value;
};


BSTnode * findNode(BSTnode * root, int value){
    if(root == NULL) return NULL;
    if(root->value == value) return root;
    else if(value < root->value) return findNode(root->left,value);
    else return findNode(root->right,value);
}

void addNode(BSTnode *& root, int value){
    BSTnode * tmp = new BSTnode;
    tmp->value = value;
    tmp->left = tmp->right = tmp->parent = NULL;
    if(root == NULL) root = tmp;
    else{
        BSTnode * p = root; // element do przeszukiwania
        BSTnode * q = NULL; // previous dla parenta
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
//nie działa jak powinno dla niektorych wartości
BSTnode *commonpred(BSTnode *x, BSTnode *y){
    if(x==NULL || y==NULL) return NULL;
    if(x==y) return x;
    else {
        if(x->parent!=NULL)
        commonpred(x->parent, y);
        if(y->parent!=NULL)
        commonpred(x, y->parent);
        if(x->parent!=NULL && y->parent!=NULL)
        commonpred(x->parent, y->parent);
    }
}

void findCommonValue(BSTnode * root ,int x, int y){
    BSTnode *a=findNode(root,x);
    BSTnode *b=findNode(root,y);
    cout<<commonpred(a,b)->value<<endl;
}

void printBST(BSTnode * root){
    if(root != NULL){
        if(root->left) printBST(root->left);
        cout << root->value << " ";
        //cout<<endl;
        if(root->right) printBST(root->right);
      //  cout<<"      ";
    }
}
int main(){
    BSTnode * tree = NULL;
    addNode(tree,15);
    addNode(tree,11);
    addNode(tree,20);
    addNode(tree,7);
    addNode(tree,12);
    addNode(tree,19);
    addNode(tree,30);
    addNode(tree,8);
    BSTnode * finded = findNode(tree,20);
   findCommonValue(tree,11,20);
    printBST(tree);
}