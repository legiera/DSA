////
//// Created by Karolina on 03.05.2018.
////
//

#include <iostream>
using namespace std;

//1. Prosze zaimplementowac funkcje wstawiajaca zadana liczbe do SkipListy przechowujacej dane
//        typu int. Prosze zadeklarowac wszystkie potrzebne struktury danych i krótko (2-3 zdania) opisac
//        zaimplementowany algorytm.

const int MAX_LEVEL =10; //bo liczby typu int
struct SLNode{
    int value;
    int level;
    SLNode ** next;
};

struct SkipList{
    SLNode * first;
    SLNode * last;
};

int getLevel(){
    int lvl=0;
    while(lvl<MAX_LEVEL && rand()<0.5)
        lvl++;
    return lvl;
}
void insert(SkipList S, int key){
    int lvl=getLevel();   //losujemy wysokośc na jakiej będziemy dodawać nowy lement
    SLNode *tmp= S.first;

    SLNode * nowy = new SLNode;  //init nowy element w celu póżniejszego wstawienia go
    nowy->value=key;            // do list
    nowy->level=lvl;
    nowy->next=new SLNode *[lvl];

    for(int i=MAX_LEVEL-1;i>=0;i--) {  //przechodzimy po poziomach aby znaleść miejsce dla key
        while (tmp->next[i] != NULL && tmp->next[i]->value < key)
            tmp = tmp->next[i];

        if(i<lvl){   //dodajemy key na każdym poziomie ?????
            nowy->next[i]=tmp->next[i]; //nie powinno być <=???
            tmp->next[i]=nowy;
        }
    }
}




//2. Prosze opisac jak zmodyfikowac drzewa czerwono-czarne (przechowujace elementy typu int) tak,
//by operacja int sum(T, x, y) obliczajaca sume elementów z drzewa o wartosciach
//        z przedziału [x, y] działała w czasie O(log n) (gdzie n to rozmiar drzewa T). Pozostałe operacje
//na powstałym drzewie powinny miec złozonosc taka sama jak w standardowym drzewie
//czerwono-czarnym. (Podpowiedz: Warto w kazdym wezle drzewa przechowywac pewna dodatkowa
//        informacje, która upraszcza wykonanie operacji sum i która mozna łatwo aktualizowac).

/*W każdym weźle będziemy przechowywać dodatkową informację sum, która będzie sumą
 * mniejszych, i równych(+key) niż klucz (parent) wartości , czyil sumą lewych dzieci , wartość tą będziemy obliczać
 * za pomocą algorytmu, który co wielkości jest dany klucz
 * aby obliczyć sumę wykonamy podany algorytm dla x i y w czasie 2 * O(logn)
 * a wynikiem będzie wartość bezwzględna różnicy obu wartości
 * */



//3. Kapitan pewnego statku zastanawia sie, czy moze wpłynac do portu mimo tego, ze nastapił
//odpływ. Do dyspozycji ma mape zatoki w postaci tablicy:
//int n = ...
//int m = ...
//int A[m][n];
//gdzie wartosc A[y][x] to głebokosc zatoki na pozycji (x, y). Jesli jest ona wieksza niz pewna
//wartosc int T to statek moze sie tam znalezc. Poczatkowo statek jest na pozycji (0, 0) a port
//znajduje sie na pozycji (n − 1,m − 1). Z danej pozycji statek moze przepłynac bezposrednio
//        jedynie na pozycje bezposrednio obok (to znaczy, na pozycje, której dokładnie jedna ze
// współrzednych rózni sie o jeden). Prosze napisac funkcje rozwiazujaca problem kapitana.



struct Node{
    int rank;
    Node *parent;
    int value;
};

struct Bay{
    int **A;
    int n;
};

Node *MakeSet(int val){
    Node * tmp =new Node;
    tmp->rank=0;
    tmp->value=val;
    tmp->parent=tmp;
    return tmp;
}

Node * FindSet(Node *p){
    if(p->parent!=p)
        return p->parent = FindSet(p->parent);

    return p;
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

        if(x->rank==y->rank){
            y->rank+=1;
        }

    }

}
//wykonujemy n*m operacji MakeSet
//n*m operacji Union w pesymistycznym przypadku
//złożoność O(n*mlog(n*m))
const int n=3,m=3;
bool canEnter(int A[n][m], int n, int m, int T){
    Node *bay[n][m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            bay[i][j]=MakeSet(A[i][j]);
    for(int i=0;i<n;i++)
        for(int j=0 ;j<m;j++)
            if(A[i][j]>T){
                if(i+1<n && A[i+1][j]>T)
                    Union(bay[i][j],bay[i+1][j]);

                if(j+1<m && A[i][j+1]>T)
                    Union(bay[i][j],bay[i][j+1]);

            }
    Node * start = FindSet(bay[0][0]);
    Node * end = FindSet(bay[n-1][m-1]);

    if(start==end) return true;
    else return false;
}

int main(){
    int A[n][m];
    A[0][0] = 5;
    A[0][1] = 5;
    A[0][2] = 5;
    A[1][0] = 5;
    A[1][1] = 5;
    A[1][2] = 5;
    A[2][0] = -1;
    A[2][1] = -1;
    A[2][2] = 2;

    if(canEnter(A,n,m,0)) cout<<"Tak"<<endl;
    else cout <<"Nie"<<endl;
}

