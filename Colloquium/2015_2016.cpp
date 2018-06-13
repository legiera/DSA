//
// Created by Karolina on 03.05.2018.
//

//1. Dane sa struktury danych opisujace SkipListe:
//struct SLNode f
//int value; // wartosc przechowywana w wezle
//int level; // poziom wezła
//SLNode** next; // level-elementowa tablica wskazników na nastepniki
//g;
//struct SkipList f
//SLNode* first; // wartownik przedni (pole value ma wartosc -1)
//SLNode* last; // wartownik tylny (pole value ma wartosc +1)
//g;
//const int MAX LEVEL = ... ; // maksymalny poziom wezłów
//Prosze zaimplementowac funkcje SkipList merge( SkipList A, SkipList B ), która scala
//dwie otrzymane SkipListy (w efekcie powstaje nowa SkipLista składajaca sie z dokładnie tych
//        samych wezłów co poprzednie; nie nalezy zmieniac poziomów wezłów). Wezły wartowników maja
//        poziom MAX LEVEL. Funkcja powinna działac mozliwie jak najszybciej. Prosze oszacowac
//złozonosc czasowa.
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
const int MAX_LEVEL=10;
struct SLNode{
    int value;
    int level;
    SLNode **next;
};

struct SkipList{
    SLNode * first;
    SLNode * last;
};


SkipList create(){
    SkipList S;
    SLNode *first = new SLNode;
    SLNode *last = new SLNode;

    first->value=INT8_MIN;
    first->level = MAX_LEVEL;
    first->next = new SLNode * [MAX_LEVEL];

    last->value=INT8_MAX;
    last->level = MAX_LEVEL;
    last->next = new SLNode * [MAX_LEVEL];

    for(int i=MAX_LEVEL-1; i>=0; i--){
        first->next[i]=last;
        last->next[i]=NULL;
    }
    S.first=first;
    S.last=last;

    return S;
}
int getLevel(){
    int lvl=1;
    while(lvl<MAX_LEVEL && rand()<0.5) lvl++;

    return lvl;
}
void insert(SkipList S, int key){
    int lvl = getLevel();
    SLNode *s=S.first;
    SLNode * tmp=new SLNode;
    tmp->value=key;
    tmp->level=lvl;
    tmp->next = new SLNode*[lvl];

    for(int i=MAX_LEVEL-1;i>=0;i--){
        while(s->next[i]!=NULL && s->next[i]->value<key)
            s=s->next[i];

        if(i<lvl){
            tmp->next[i]=s->next[i];
            s->next[i]=tmp;
        }
    }
}


SkipList merge(SkipList A, SkipList B){
    SkipList C = create();
    SLNode *a=A.first;
    SLNode *b=B.first;
    SLNode *c=C.first;

    SLNode ** t = new SLNode *[MAX_LEVEL];
    for (int i = 0; i < MAX_LEVEL; i++)
        t[i] = c;

    for(int i = MAX_LEVEL-1 ;i>=0;i--){
        while(a->next[i]->value!=INT8_MAX || b->next[i]->value!=INT8_MAX){
            SLNode *p;
            if(a->next[i]->value<b->next[i]->value){
                p=a->next[i];
                a->next[i] = a->next[i]->next[i];
            }
            else{
                p=b->next[i];
                b->next[i]=b->next[i]->next[i];
            }

            p->next[i]=t[i]->next[i];
            t[i]->next[i] = p;
            t[i] = p;
        }
    }
    delete[] t;

    return C;

}

void show(SkipList skip) {
    SLNode * s = skip.first;
    while (s->next[0] != NULL) {
        cout << s->value << " ";
        s = s->next[0];
    }
    cout << endl;
}


//2. Prosze opisac (bez implementacji) algorytm, który otrzymuje na wejsciu pewne drzewo BST T
//i tworzy nowe drzewo BST T0, które spełnia nastepujace warunki: (a) T0 zawiera dokładnie te
//same wartosci co T, oraz (b) drzewo T0 jest drzewem czerwono-czarnym (w zwiazku z tym
//        powinno zawierac kolory wezłów).
//druga grupa: AVL
/* przechowujemy klucze w tablicy, wyciągajac je inorder O(logn) dzięki czemu są posortowane
 * lub sortujemy tablice
 * przechodzimy rekurencyjnie wyznaczając parent, środek tablicy jest korzeniem, środek lewej podtablicy
 * jest lewym dzieckiem, środek prawej podtablicy jest prawym dzieckiem, wykonujemy dopóki nie skończy
 * nam sie tablica
Dzięki temu powstaje drzewo wyważone, po powstaniu drzewa przechodzimy od dołu w celu uzupełnienia wartości
 wyważenia drzewa

 dla czerwono-czarnego dodatkowo kolorujemy wezły tak aby poziomami się zgadzały, korzen jest czarny, czyli środek
 tablicy, dzieci bedą czerwone, następne wywolania rekurencyjne dla wnuków korzenia będą czarne itd.
 zamiana koloru względem uzupełniania kolejnego poziomu
 */


//3. W ramach obchodów miedzynarodowego swieta cyklistów organizatorzy przewidzieli górska
//        wycieczke rowerowa. Bedzie sie ona odbywac po bardzo waskiej sciezce, na której rowery moga
//        jechac tylko jeden za drugim. W ramach zapewnienia bezpieczenstwa kazdy rowerzysta bedzie
//        miał numer identyfikacyjny oraz małe urzadzenie, przez które bedzie mógł przekazac
//        identyfikator rowerzysty przed nim (lub -1 jesli nie widzi przed soba nikogo). Nalezy napisac
//funkcje, która na wejsciu otrzymuje informacje wysłane przez rowerzystów i oblicza rozmiar
//        najmniejszej grupy (organizatorzy obawiaja sie, ze na małe grupy mogłyby napadac dzikie
//zwierzeta). Dane sa nastepujace struktury danych:
//struct Cyclist f
//int id, n id; // identyfikator rowerzysty oraz tego, którego widzi
//g;
//Funkcja powinna miec prototyp int smallestGroup( Cyclist cyclist[], int n ), gdzie
//cyclist to tablica n rowerzystów. Funkcja powinna byc mozliwie jak najszybsza. Mozna załozyc,
//        ze identyfikatory rowerzystów to liczby z zakresu 0 do 108 (osiem cyfr napisanych w dwóch
//        rzedach na koszulce rowerzysty) i ze pamiec nie jest ograniczona. Rowerzystów jest jednak duzo
//mniej niz identyfikatorów (nie bez powodu boja sie dzikich zwierzat). Nalezy zaimplementowac
//wszystkie potrzebne struktury danych.

struct Cyclist{
    int id;
    int n_id;
};

struct Node{
    int size;
    Node *parent;
};

Node *MakeSet(int val){
    Node *tmp=new Node;
    tmp->size=1;
    tmp->parent=tmp;
    return tmp;
}
Node * FindSet(Node *x){
    if(x->parent!=x)
        return x->parent = FindSet(x->parent);

    return x;
}
void Union(Node *x, Node *y){
    x=FindSet(x);
    y=FindSet(y);
    if(x==y) return;

    if(x->size>y->size){
        y->parent=x;
        x->size+=y->size;
    }
    else{
        x->parent=y;
        y->size+=x->size;
    }
}

//n*n operacji union i n operacji makeset=> n*nlogn
int smallestGroup( Cyclist cyclist[], int n ){
    Node *Group[n];
    for(int i=0;i<n;i++)
        Group[i]=MakeSet(cyclist[i].id);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(cyclist[i].n_id==cyclist[j].id)
                Union(Group[i],Group[j]);
            if(cyclist[j].n_id==cyclist[i].id)
                Union(Group[i],Group[j]);
        }
    }
    int small=n;
    int p;
    for(int i=0;i<n;i++){
        p=FindSet(Group[i])->size;
        if(small>p) small=p;

    }
    return small;
}




const int ID_MAX = 1000;
const int CYCLIST_COUNT = 10;

//typedef struct Cyclist {
//    int id, n_id;           //identyfiktor rowerzysty oraz tego, ktorego widzi
//} Cyclist;

typedef struct Group {
    int first_id;           //identyfikator pierwszej osoby, potem jest identyfikatorem osoby, dla ktorej szukamy osoby, ktora go widzi
    int size;               //rozmiar grupy
} Group;


Cyclist *generate_data() {
    srand(time(NULL));
    bool *B = (bool *) calloc(sizeof(bool), CYCLIST_COUNT);
    Cyclist *C = (Cyclist *) calloc(sizeof(Cyclist), CYCLIST_COUNT);

    for (int i = 0; i < CYCLIST_COUNT; ++i) {
        C[i].id = rand() % ID_MAX;
    }

    C[0].n_id = -1;
    for (int i = 1; i < CYCLIST_COUNT; ++i) {

        if (rand() % 4 == 0)
            C[i].n_id = -1;
        else {
            int x = rand() % CYCLIST_COUNT;
            while (B[x]) {                          //lata na sytuacje, w ktorej dwaj rowerzysci maja przed soba ta sama osobe
                x = rand() % CYCLIST_COUNT;         //jada gesiego => sytuacja niemozliwa
            }

            C[i].n_id = C[x].id;
            B[x] = true;
        }
    }

    return C;
}


int smallest_group(Cyclist *cyclist, int n) {
    Group*G = (Group*)calloc(sizeof(Group),n);

    bool*B = (bool*)calloc(sizeof(bool),n);

    int min_group_size = n;
    int group_count = 0;
    int j = 0;

    for (int i = 0; i < CYCLIST_COUNT; ++i) {

        if (cyclist[i].n_id == -1){             //znalezienie pierwszych osob w grupie
            G[j].first_id = cyclist[i].id;      //ustawienie
            G[j].size++;

            B[i] = true;                            //ustawienie ze przewtorzono
            group_count++;
            j++;
        }
    }

    for (int i = 0; i < CYCLIST_COUNT; ++i) {
        if (!B[i]) {
            for (int j = 0; j < group_count; ++j) {
                if (cyclist[i].n_id ==  G[j].first_id){
                    G[j].size++;
                    G[j].first_id = cyclist[i].id;
                    B[i] = true;
                    i = -1;
                    break;
                }
            }
        }
    }

    int p;
    for (int i = 0; i < group_count; ++i) {
        if (G[i].size < min_group_size) {
            min_group_size = G[i].size;
            p=G[i].first_id;
        }
    }
    cout<<p<<endl;
    return min_group_size;
}

int main() {
//    srand(time(NULL));
//    SkipList A, B;
//    A = B = { NULL, NULL };
//
//    A=create();
//    B=create();
//
//    insert(A, 1);
//    insert(A, 2);
//    insert(A, 3);
//
//    show(A);
//
//    insert(B, 4);
//    insert(B, 5);
//    insert(B, 8);
//    insert(B, 7);
//
//
//    show(B);
//
//    SkipList C = merge(A, B);
//    show(C);
//
//    return 0;

    smallest_group(generate_data(),100);

    Cyclist*c = generate_data();
    for (int i = 0; i < CYCLIST_COUNT; ++i) {
        cout << c[i].id << " ";
    }
        cout << endl;

    for (int i = 0; i < CYCLIST_COUNT; ++i) {
        cout <<c[i].n_id << " ";
    }
    cout << endl;
    Cyclist *d= new Cyclist[4];
    d[0].id=400;
    d[1].id=811;
    d[2].id=432;
    d[3].id=538;

    d[0].n_id=811;
    d[1].n_id=432;
    d[2].n_id=538;
    d[3].n_id=-1;

    //cout << smallest_group(c,CYCLIST_COUNT)<<endl;
    cout << smallestGroup(c,CYCLIST_COUNT)<<endl;

  //  cout << smallest_group(d,4)<<endl;
    cout << smallestGroup(d,4)<<endl;
}

