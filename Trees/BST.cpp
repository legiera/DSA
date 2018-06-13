#include<iostream>
using namespace std;

struct BSTnode{
    BSTnode * parent;
    BSTnode * left;
    BSTnode * right;
    int value;
};

BSTnode * findBSTnode(BSTnode * root, int value){
    if(root == NULL) return NULL;
    if(root->value == value) return root;
    else if(value < root->value) return findBSTnode(root->left,value);
    else return findBSTnode(root->right,value);
}

void addBSTnode(BSTnode *& root, int value){
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

int getMin(BSTnode * root){
    while(root->left != NULL) root = root->left;
    return root->value;
}

BSTnode *getMinNode(BSTnode * root){
    while(root->left != NULL) root = root->left;
    return root;
}
int getMax(BSTnode * root){
    while(root->right != NULL) root = root->right;
    return root->value;
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

BSTnode * prev(BSTnode * node){
    if(node->left != NULL){
        node = node->left;
        while(node->right != NULL) node = node->right;
        return node;
    }
    else{
        while(node->parent != NULL && node->parent->value > node->value) node = node->parent;
        return node;
    }
}

int countInterval(BSTnode * T, int a, int b){
    if(!T) return 0;
    if(T->value == b && T->value == a) return 1;
    if(T->value <= b && T->value >= a) return 1 + countInterval(T->left,a,b) + countInterval(T->right,a,b);
    else if(T->value < a) return countInterval(T->right,a,b);
    else return countInterval(T->left,a,b);
}

int sumBST(BSTnode * T){
    if(!T) return 0;
    if(T->left == NULL && T->right == NULL) return T->value;
    else return T->value + sumBST(T->left) + sumBST(T->right);
}

int nodesAmount(BSTnode * T){
    if(!T) return 0;
    if(T->left == NULL && T->right == NULL) return 1;
    else return 1 + nodesAmount(T->left) + nodesAmount(T->right);
}

double avarge(BSTnode * T){ return sumBST(T) / nodesAmount(T);}

double avarge2(BSTnode * T, double & count, double & sum){
	if(T == NULL) return 0;
	avarge2(T->left,count,sum);
	avarge2(T->right,count,sum);
	if(T != NULL){
		sum += T->value;
		count++;
	}
	if(T->parent == NULL) return sum / count;
}

BSTnode * getBSTnode(BSTnode *& root, BSTnode * z){
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

void deleteTree(BSTnode * root){
    if(root != NULL){
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

void printBST(BSTnode * root){
    if(root != NULL){
        if(root->left) printBST(root->left);
        cout << root->value << " ";
        if(root->right) printBST(root->right);
    }
}

//https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
BSTnode* deleteBSTnode(BSTnode* root, int value){

    if (root == NULL) return root;

    if (value < root->value)
        root->left = deleteBSTnode(root->left, value);

    else if (value > root->value)
        root->right = deleteBSTnode(root->right, value);

    else{

        if (root->left == NULL){
            BSTnode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL){
            BSTnode *temp = root->left;
            free(root);
            return temp;
        }

        BSTnode* temp = getMinNode(root->right);
        root->value = temp->value;

        root->right = deleteBSTnode(root->right, temp->value);
    }
    return root;
}
int howhigh(BSTnode* root, int val){
    BSTnode *tmp=findBSTnode(root,val);
    if(tmp==NULL) return 0;
    int count =0;
    while(tmp!=NULL && tmp->value<=val){
        count++;
        count+=nodesAmount(tmp->left);
        tmp=tmp->parent;
    }
    return count;
}

int main(){
    BSTnode * tree = NULL;
    addBSTnode(tree,15);
    addBSTnode(tree,11);
    addBSTnode(tree,20);
    addBSTnode(tree,7);
    addBSTnode(tree,12);
    addBSTnode(tree,19);
    addBSTnode(tree,30);
    addBSTnode(tree,8);
 //   BSTnode * finded = findBSTnode(tree,20);
   // BSTnode * removed = getBSTnode(tree,finded);
    double c = 0, s = 0;
    cout << "ilosc z przedzialu [a,b] to " << countInterval(tree,5,12) << endl;
    cout << "suma wartosci wezlow w drzewie to " << sumBST(tree) << endl;
    cout << "ilosc wezlow w drzewie to " << nodesAmount(tree) << endl;
    cout << "srednia wartosc wezla to " << avarge2(tree,c,s) << endl;
    cout << "który z kolei w drzewie " << howhigh(tree,20) << endl;
    cout << "który z kolei w drzewie " << howhigh(tree,30) << endl;
    cout << "który z kolei w drzewie " << howhigh(tree,15) << endl;
    cout << "który z kolei w drzewie " << howhigh(tree,7) << endl;
    cout << "który z kolei w drzewie " << howhigh(tree,8) << endl;



    cout<< "succ "<<prev(findBSTnode(tree,7))->value<<endl;
    printBST(tree);
}
