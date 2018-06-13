//
// Created by Karolina on 09.05.2018.
//

#include <iostream>
#include <queue>
using namespace std;

struct Node{
    Node *right,*left,*parent;
    int value;
};

bool find(Node *A, int val){
    Node* p=A;
    while(p!=NULL){
        if(val==p->value) return true;
        else if(val<p->value) p=p->left;
        else p=p->right;
    }
    return false;
}


void insert(Node *&root, int val){

    Node *n=new Node;
    n->parent=n->left=n->right=NULL;
    n->value=val;
    if(root==NULL) root = n;
    else {
        Node *p = root;
        Node *q = NULL;
        while(p!=NULL){
            if(p->value<n->value) {
                q = p;
                p=p->right;
            }
            else{
                q=p;
                p=p->left;
            }
        }
        if(q->value<n->value) q->right=n;
        else q->left=n;
        n->parent=q;
    }
}
Node *getMinNode(Node * root){
    while(root->left != NULL) root = root->left;
    return root;
}

Node* deleteNode(Node* &root, int value){

    if (root == NULL) return root;

    if (value < root->value)
        root->left = deleteNode(root->left, value);

    else if (value > root->value)
        root->right = deleteNode(root->right, value);

    else{

        if (root->left == NULL){
            Node *temp = root->right;
           // free(root);
            return temp;
        }
        else if (root->right == NULL){
            Node *temp = root->left;
           // free(root);
            return temp;
        }

        Node* temp = getMinNode(root->right);
        root->value = temp->value;

        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

void printBST(Node * root){
    if(root != NULL){
        if(root->left) printBST(root->left);
        cout << root->value << " ";
        if(root->right) printBST(root->right);
    }
}

Node *Merge(Node *A, Node *B){
    queue<Node*>Q;
    if(A!=NULL) Q.push(A);
    else return NULL;
    Node *C=B;
    //cout<<"ddd"<<endl;
    while(!Q.empty()) {
        //cout << "ddd" << endl;

        Node *u = Q.front();
        Q.pop();
        if (u->left != NULL) Q.push(u->left);
        if (u->right != NULL) Q.push(u->right);
        if (!find(C, u->value)) {
            insert(C, u->value);
            cout << "ddd" << endl;
        }
        else deleteNode(C,u->value);
       // printBST(C);

    }
    return C;
}

int main() {

    Node *tree = NULL;
    insert(tree, 15);
    insert(tree, 11);
    insert(tree, 20);
    insert(tree, 7);
    insert(tree, 12);
    insert(tree, 19);
    insert(tree, 30);
    insert(tree, 8);
    printBST(tree);
    cout<<endl;
    Node *tree1 = NULL;
    insert(tree1, 15);
    insert(tree1, 10);
    insert(tree1, 20);
    insert(tree1, 7);
    printBST(tree1);
//zwraca drzewo bez przecięć

    Node * tree3=Merge(tree,tree1);
    printBST(tree3);
}