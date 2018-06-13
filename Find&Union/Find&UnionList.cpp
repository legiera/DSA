//
// Created by Karolina on 05.05.2018.
//

#include <iostream>
using namespace std;

struct node;

struct set {
    node * head;
    node * tail;
    int length;
};

struct node {
    set * R;		// reprezentant - struktura set
    node * next;
    int V;
};

set * findset(node *c)
{
    return c->R;
}

set * makeset(int v) // tworzy nowy zbiór (z jednego wierzchołka - v)
{
    set * S = new set;
    node * N = new node;

    N->R = S;
    N->next = NULL;
    N->V = v;
    S->head = N;
    S->tail = N;
    S->length = 1;

    return S;
}

set * unionsets(set * &A, set * &B)		// scala listy, zwraca strukturę set z połączonych list
{
    if (A->length <= B->length)				// musi przestawiać R - trzeba zmodyfikowac
    {
        A->tail->next = B->head;
        A->tail = B->tail;
        A->length += B->length;
        node * temp = B->head;
        while (temp != NULL)
        {
            temp->R = A;
            temp = temp -> next;
        }
        return A;
    }
    else
    {
        B->tail->next = A->head;
        B->tail = A->tail;
        B->length += A->length;
        node * temp = A->head;
        while (temp != NULL)
        {
            temp->R = B;
            temp = temp->next;
        }
        return B;
    }
}