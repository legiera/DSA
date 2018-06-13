

#include <iostream>
using namespace std;
//
// Created by Karolina on 03.05.2018.
//
//
//B
//1. Prosze zaimplementowac funkcje usuwajaca zadana liczbe ze SkipListy przechowujacej dane
//typu int. Prosze zadeklarowac wszystkie potrzebne struktury danych i krótko (2-3 zdania) opisac
//        zaimplementowany algorytm.
const int MAX_LEVEL=10;
struct SLNode{
    int value;
    int level;
    SLNode **next;
};

struct SkipList{
    SLNode *first;
    SLNode *last;
};

void remove(SkipList S, int key){
    SLNode * tmp = S.first;
    SLNode * del;
    for( int i=MAX_LEVEL-1;i>=0;i--) {
        while (tmp->next[i] != NULL && tmp->next[i]->value < key)
            tmp = tmp->next[i];

        if (tmp->next[i]->value == key){
            del=tmp->next[i];
            tmp->next[i]=del->next[i];
        }
    }
    if(tmp->next[0]->value != key) return;
    delete del->next[0];

}

//2. Prosze opisac jak zmodyfikowac drzewa AVL (przechowujace elementy typu int) tak, by
//        operacja int findRandom(T) zwracajaca losowo wybrany element z drzewa T działała w czasie
//O(log n). Funkcja findRandom powinna zwracac kazdy element z drzewa z takim samym
//        prawdopodobienstwem. Do dyspozycji maja Panstwo funkcje int random( int k ), która
//zwraca liczbe ze zbioru f0, ..., k − 1g zgodnie z rozkładem jednostajnym. Pozostałe operacje na
//        powstałym drzewie powinny miec złozonosc taka sama jak w standardowym drzewie AVL.
//(Podpowiedz: Warto w kazdym wezle drzewa przechowywac pewna dodatkowa informacje, która
//upraszcza wykonanie operacji findRandom i która mozna łatwo aktualizowac).

/* Dodatkowo w kazdym weźłe będziemy przetrzymywać: daną odnośnie k- co do wielkości klucza
 * Dzięki własności drzewa AVL wiemy że każde lewe(prawe) poddrzewo jest albo mniejsze lub większe, lub równe o 1
 * dzięki wartości wyważenia drzewa , dzięki temu uzyskamy odp ile jest elementów w danym podrzewie i będziemy wstanie
 * odpowiednio dobrać funkcje random, aktualizacja danych będzie zachodzic za pomocą funkcji sprawdzajacej, jaki co do w
 * wielkości jest dany klucz w czasie O(logn)*/

//3. Dana jest tablica:
//int n = ...
//int m = ...
//bool A[m][n];
//Gracz poczatkowo znajduje sie na (zadanej) pozycji (x, y), dla której zachodzi A[y][x] == true.
//Z danej pozycji wolno bezposrednio przejsc jedynie na pozycje, której dokładnie jedna
//        współrzedna rózni sie o 1, oraz której wartosc w tablicy A wynosi true. Prosze napisac program
//        obliczajacy do ilu róznych pozycji moze dojsc gracz startujac z zadanej pozycji (x, y).

struct Node{
    int value;
    int rank;
    Node * parent;
};

Node * MakeSet(int val){
    Node * x= new Node;
    x->value=val;
    x->rank=1; //powinno być 0 ale jak przy dodawaniu nie będzie odp działało
    x->parent=x;

    return x;
}

Node *FindSet(Node *x){
    if(x->parent!=x)
        return x->parent=FindSet(x->parent);

    return x;
}

void Union(Node *x, Node *y){
    x=FindSet(x);
    y=FindSet(y);

    if(x==y) return;
    if(x->rank>y->rank){
        y->parent=x;
        x->rank+=y->rank;

    }
    else{
        x->parent=y;
        y->rank+=x->rank;
        if(x->rank==y->rank)
            y->rank+=1;

    }
}
bool A[3][3];

int canEnter(int n, int m, int x, int y){
    Node *bey[n][m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            bey[i][j]=MakeSet(A[i][j]);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(A[i][j]){
                if(i+1<n && A[i+1][j]) Union(bey[i][j],bey[i+1][j]);
                if(j+1<m && A[i][j+1]) Union(bey[i][j],bey[i][j+1]);
            }


    Node *res=FindSet(bey[x][y]);
    return res->rank;
}

int main(){

    A[0][0] = true;
    A[0][1] = false;
    A[0][2] = true;
    A[1][0] = false;
    A[1][1] = false;
    A[1][2] = true;
    A[2][0] = false;
    A[2][1] = false;
    A[2][2] = true;

    int resultat = canEnter(3,3,0,2);
    cout << resultat <<endl;
}