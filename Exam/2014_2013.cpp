//
// Created by Karolina on 03.05.2018.
//
//
//2.Proszę zaimplementować algorytm, który mając na wejsciu
//dwa drzewa BST (przechowujące liczby typu int; proszę zadeklarowa odpowiednie struktury danych)
// zwraca nowe drzewo BST, zawierające wyłącznie te liczby, które występują w obu drzewach.
// Algorytm powinien być jak najszybszy i wykorzystywać jak najmniej pamięci.
//Jaka jest złożoność zaproponowanego algorytmu?
//Co można powiedzieć o zrównoważeniu drzew tworzonych przez zaproponowany algorytm?

//druga wersja:merge elem które nie wystęują w obu drzewach


#include<iostream>
using namespace std;

struct BSTnode{
    BSTnode * parent;
    BSTnode * left;
    BSTnode * right;
    int value;
};

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


void printBST(BSTnode * root){
    if(root != NULL){
        if(root->left) printBST(root->left);
        cout << root->value << " ";
        if(root->right) printBST(root->right);
    }

}
void mergeTree(BSTnode * T, BSTnode * R, BSTnode *& finalTree){
    if(T == NULL || R == NULL) return;
    if(T->value == R->value) addNode(finalTree,T->value);
    if(T->value < R->value){
        mergeTree(T->right,R,finalTree);
        mergeTree(T,R->left,finalTree);
    }
    else{
        mergeTree(T->left,R,finalTree);
        mergeTree(T,R->right,finalTree);
    }
}
BSTnode * findNode(BSTnode * root, int value){
    if(root == NULL) return NULL;
    if(root->value == value) return root;
    else if(value < root->value) return findNode(root->left,value);
    else return findNode(root->right,value);
}
BSTnode * succ(BSTnode * node){
    if(node->right != NULL){
        node = node->right;
        while(node->left != NULL) node = node->left;
        return node;
    }
    else{
        while(node->parent != NULL && node->parent->value < node->value) node = node->parent;
        return node;
    }
}
BSTnode * getNode(BSTnode *& root, BSTnode * z){
    BSTnode * y, * x;
    if(z->left == NULL || z->right == NULL) y = z;
    else y = succ(z);
    if(y->left != NULL) x = y->left;
    else x = y->right;
    if(x != NULL) x->parent = y->parent;
    if(y->parent == NULL) root = x;
    else if(y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    if(y != z) z->value = y->value;
    return y;
}
void deleteNode(BSTnode *& T, int value){
    BSTnode * finded = findNode(T,value);
    BSTnode * removed = getNode(T,finded);
}
void combined(BSTnode * root, BSTnode *& newTree){
    if(root != NULL){
        if(root->left) combined(root->left,newTree);
        BSTnode * node = findNode(newTree,root->value);
        if(node == NULL) addNode(newTree,root->value);
        else BSTnode * removed = getNode(newTree,node);
        if(root->right) combined(root->right,newTree);

    }
}
//lepszy pomysł, mergować dwa drzewa normalnie ale w funkcji addnode gdy będziemy chceli dodać zdublowaną wartośc
//po prostu ją usuniemy

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
    double c = 0, s = 0;

    printBST(tree);
    cout<<endl;
    BSTnode * tree1 = NULL;
    addNode(tree1,16);
    addNode(tree1,12);
    addNode(tree1,21);
    addNode(tree1,8);
    addNode(tree1,13);
    addNode(tree1,20);
    addNode(tree1,31);
    addNode(tree1,9);
    printBST(tree1);
    cout<<endl;
    BSTnode * finalTree1 = NULL;
    combined(tree,finalTree1);
    combined(tree1,finalTree1);

    printBST(finalTree1);
    cout<<endl;
    BSTnode * finalTree = NULL;
    mergeTree(tree,tree1,finalTree);
    printBST(finalTree);
    cout<<endl;



}