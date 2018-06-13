//
// Created by Karolina on 07.05.2018.
//

#include <iostream>
#include <cstdlib>
using namespace std;

struct Node{
    Node *parent;
    int val;
    int rank;
};

Node * MakeSet(int x){
    Node * p=new Node;
    p->parent=p;
    p->rank=0;
    p->val=x;
    return p;
}

Node * Find(Node *p){
    if(p->parent!=p)
        return p->parent = Find(p->parent);

    return p;
}
//czemu nie ma update rank?? przecież łączymy dwa zbiory więc licznosc się zwiększa
void Union(Node *x, Node *y){
    x=Find(x);
    y=Find(y);
    if(x==y) return;
    if(x->rank >y->rank)
        y->parent=x;

    else{
        x->parent=y;
        if(x->rank==y->rank)
            y->rank+=1;
    }
}
