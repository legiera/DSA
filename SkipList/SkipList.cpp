//
// Created by Karolina on 11.04.2018.
//

// SkipLista.cpp: Określa punkt wejścia dla aplikacji konsoli.
//

//#include "stdafx.h"
#include <iostream>
#include <cstdlib>
using namespace std;

const int MAX_LEVEL = 3;
const int min_ = -259789;
const int max_ = 265785;

struct SLNode
{
    int value;
    int level;
    SLNode ** next;
};

struct SkipList
{
    SLNode * first;
    SLNode * last;
};

int getlevel()
{
    int lvl = 1;
    while (lvl < MAX_LEVEL && rand() < 0.5) lvl++;
    return lvl;
}

//tworzenie nowej SkipListy
SkipList create()
{
    SkipList S;

    //inicjowanie strażników
    SLNode * first = new SLNode;
    first->value = min_;
    first->level = MAX_LEVEL;
    first->next = new SLNode * [MAX_LEVEL];

    SLNode * last = new SLNode;
    last->value = max_;
    last->level = MAX_LEVEL;
    last->next = new SLNode * [MAX_LEVEL];

    //przyporządkowanie wskaźników dla każdego levelu

    for (int i = MAX_LEVEL - 1; i >= 0; i--)
    {
        first->next[i] = last;
        last->next[i] = NULL;
    }

    //przypisanie strażników do SkipListy

    S.first = first;
    S.last = last;

    return S;
}

//dodawanie inta
void insert(SkipList S, int key)
{
    int l = getlevel();
    SLNode * tmp = S.first;

    //tworzenie nowego węzła który dodamy
    SLNode * nowy = new SLNode;
    nowy->value = key;
    nowy->level = l;
    nowy->next = new SLNode *[l];

    for (int i = MAX_LEVEL - 1; i >= 0; i--)
    {
        //szukanie miejsca do dodania
        while (tmp->next[i] != NULL && tmp->next[i]->value < key)
            tmp = tmp->next[i];

        //wstawienie nowego węzła
        if (l > i)
        {
            nowy->next[i] = tmp->next[i];
            tmp->next[i] = nowy;
        }
    }
}

//usuwanie inta
void remove(SkipList S, int key)
{
    SLNode * tmp = S.first;
    SLNode * del;

    for (int i = MAX_LEVEL - 1; i >= 0; i--)
    {
        //szukanie miejsca węzła
        while (tmp->next[i] != NULL && tmp->next[i]->value < key)
            tmp = tmp->next[i];

        //wstawienie nowego węzła
        if(tmp->next[i]->value == key)
        {
            del = tmp->next[i];
            tmp = del->next[i];
        }
    }

    if (tmp->next[0]->value != key) return;
    delete del->next[0];


}

//scalenie dwóch SkipList
SkipList merge(SkipList A, SkipList B) {
    SkipList C = { NULL, NULL };
    C=create();

    SLNode * a = A.first;
    SLNode * b = B.first;
    SLNode * c = C.first;
    SLNode ** t = new SLNode *[MAX_LEVEL];
    for (int i = 0; i < MAX_LEVEL; i++)
        t[i] = c;

    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (a->next[i]->value != max_ || b->next[i]->value != max_) {
            SLNode * p;
            if (a->next[i]->value < b->next[i]->value) {
                p = a->next[i];
                a->next[i] = a->next[i]->next[i];

            } else {
                p = b->next[i];
                b->next[i] = b->next[i]->next[i];
            }

            p->next[i] = t[i]->next[i];
            t[i]->next[i] = p;
            t[i] = p;
        }
    }

    delete[] t;

    return C;
}


//wyszukiwanie elementu w SkipLiście
bool find(SkipList S, int key)
{
    SLNode * tmp = S.first;

    for (int i = MAX_LEVEL - 1; i >= 0; i--)
    {
        while (tmp->next[i] != NULL && tmp->next[i]->value < key)
            tmp = tmp->next[i];
    }
    if (tmp->next[0]->value == key) return true;
    return false;
}

int main()
{
    SkipList A= create();
    SkipList B = create();

    insert(A, 5);
    insert(A, 7);
    insert(A, 8);

    insert(B, 4);
    insert(B, 6);
    insert(B, 10);

    remove(B, 6);
    remove(A, 5);

    if (find(A, 7)) cout << "got' em" << endl;

    SLNode * tmpA = A.first;
    while (tmpA->next[0] != A.last)
    {
        cout << tmpA->next[0]->value<<"\t";
        tmpA = tmpA->next[0];
    }
    cout << endl;

    SLNode * tmpB = B.first;
    while (tmpB->next[0] != B.last)
    {
        cout << tmpB->next[0]->value << "\t";
        tmpB = tmpB->next[0];
    }
    cout << endl;

    SkipList S = merge(A, B);
    cout<<"merge"<<endl;
    SLNode * tmpS = S.first;
    while (tmpS->next[0] != S.last)
    {
        cout << tmpS->next[0]->value << "\t";
        tmpS = tmpS->next[0];
    }
    cout << endl;


   // system("pause");
    return 0;
}
