
#include <iostream>
using namespace std;

//
// Created by Karolina on 03.05.2018.
//
//
//1.Drzewo BST jest opisane przez strukturę:
//
//struct BST {
//    BST *left, *right;
//    int value;
//};
//Proszę zaimplementować funkcję int countInterval(BST *T, int a, int b), która oblicza ile liczb z zadanego przedziału
//domkniętego [a,b] znajduje się w drzewie T.
//
struct BSTnode{
    BSTnode * parent;
    BSTnode * left;
    BSTnode * right;
    int value;
};
int countInterval(BSTnode * T, int a, int b){
    if(!T) return 0;
    if(T->value == b && T->value == a) return 1;
    if(T->value <= b && T->value >= a) return 1 + countInterval(T->left,a,b) + countInterval(T->right,a,b);
    else if(T->value < a) return countInterval(T->right,a,b);
    else return countInterval(T->left,a,b);
}

//2.
//Dana jest struktura danych opisująca tab hasz, która przechowuje liczby
//typu int indeksowane napisami:
//
//struct HT{
//    string *key; //tab na klucze danych
//    int *data;//tab na dane
//    bool * free;//pole wolne czy zajęte
//    int size; //rozmiar tablicy
//};
//
//Tablica wykorzystuje funkcje haszująca int hash(string key, int size), która
//zwraca pozycję w tablicy na której powinny się znaleźć dane o kluczu key.
//Stosowane jest liniowe rozwiązywanie kolizji. Proszę zaimplementować funkcję
//double avarageAccess(HT * ht), która oblicza jaka jest średnia ilość pól w tablicy,
//które musi sprawdzić standardowy algorytm wyszukujący gdy poszukuje losowo wybranego
//klucza znajdującego się w tablicy ht.
struct HT{
    string *key; //tab na klucze danych
    int *data;//tab na dane
    bool * free;//pole wolne czy zajęte
    int size; //rozmiar tablicy
};

//funkcja haszująca
int getHash(string data,int size)
{
    return  stoi(data)%size;
}
int findindex(HT * HT, string key,int &sum)//so keep looking
{
    int x = getHash(key,HT->size);
    //int index = x % HT->size;
    int i = 0;
    while (HT->size > i)
    {
        if (HT->data[x] == stoi(key) && HT->free[x] == true) {
            sum+=i;
            return x;
        }
        if (HT->free[x] == false) {
            sum+=i;
            return x;
        }

        x = (x + 1) % HT->size;
        i++;
    }
    return -1;
}

double avarageAccess(HT * ht){
    int sum=0;
    for(int i=0;i<ht->size;i++)
        findindex(ht,ht->key[i],sum);
    return sum/ht->size;
}