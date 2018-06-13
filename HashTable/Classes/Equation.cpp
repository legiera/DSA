//
// Created by Karolina on 03.05.2018.
//


#include "stdafx.h"
#include <iostream>
using namespace std;

//Zadanie 4
//Tablica liczb całkowitych  T[n]. Napisać algorytm czy dla danego x czy istnieją i, j takie że T[i] + T[j] = x


bool checksum( int x, int *A, int n)
{
    HT*t = new HT();
    t->A = new HTe[2*n];
    t->A.size= 2*m;

    for( int i=0; i<n; i++)
    {
        if (findHT(t, A[i]) != -1) return true;
        insertHT(t, x-A[i]);
    }

    return false;

   // wstawia element o danym kluczu i sprawdza czy element istnieje
}
