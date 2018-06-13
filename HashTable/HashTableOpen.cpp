//
// Created by Karolina on 11.04.2018.
//


#include <iostream>
using namespace std;

//struktury do adresowania otwartego
enum Status { freeToGo, taken, keep_looking };

struct Data {
    int value;
    //Data * next;
};

struct HashTable {
    Data ** data;
    Status * status;
    int size;
};

//funkcja haszująca
int getHash(Data * data)
{
    return  data->value;
}

//funkcja pomocnicza znajdź indeks
int findindex(HashTable * HT, Data * data, bool sokl)//so keep looking
{
    Status status;
    int x = getHash(data);
    //int index = x % HT->size;
    int i = 0;
    while (HT->size > i)
    {
        if (HT->data[x] == data && HT->status[x] == taken) return x;
        if (HT->status[x] == freeToGo) return x;
        if (HT->status[x] == keep_looking && sokl == false) return x;

        x = (x + 1) % HT->size;
        i++;
    }
    return -1;
}

//szukanie adresowanie otwarte
int find(HashTable * HT, Data * data)
{
    //ustalanie indeksu
    int index = findindex(HT, data, true);
    if (index == -1) return -1;

    if (HT->status[index] == taken && HT->data[index] == data) return index;

    return -1;
}

//dodawanie adresowanie otwarte
void insert(HashTable * HT, Data * data)
{
    //ustalanie indeksu
    int index = findindex(HT, data, false); //dodawanie gdy status == keep looking lub free więc sokl == true
    if (index == -1) return;


    HT->status[index] = taken;
    HT->data[index] = data;



}

//usuwanie adresowanie otwarte
void remove(HashTable * HT, Data * data)
{
    //ustalanie indeksu
    int index = findindex(HT, data, true);
    if (index == -1) return;

    HT->status[index] = keep_looking;
    HT->data[index] = NULL;
}

int main()
{
    //tworzenie HashTable
    HashTable * HT = new HashTable;
    HT->size = 4;
    HT->data = new Data *[HT->size];
    Status status = freeToGo;


    //ustawianie wszystkich pól na NULL
    for (int i = 0; i < HT->size; i++)
    {
        HT->data[i] = NULL;
        //HT->status[i] = freeToGo;
    }



    //Tworzenie danych
    Data * data = new Data;
    data->value = 1;
    //data->next = NULL;

    Data * data1 = new Data;
    data1->value = 2;
    //data1->next = NULL;

    Data * data2 = new Data;
    data2->value = 3;
    //data2->next = NULL;

    Data * data3 = new Data;
    data3->value = 7;
    //data3->next = NULL;

    Data * data4 = new Data;
    data4->value = 4;
    //data4->next = NULL;

    insert(HT, data);
    insert(HT, data1);
    insert(HT, data2);
    insert(HT, data4);
    //insert(HT, data4);

    //remove(HT, data3);
    //remove(HT, data);

    //wyswietlenie HashTable
    for (int i = 0; i < HT->size; i++)
    {
        if (HT->data[i] != NULL)
        {
            cout << HT->data[i]->value <<endl;
        }
    }

    //if (find(HT, data4)) cout << "got it!!" << endl;
    //else cout << "couldn't find it ;c" << endl;

//    system("pause");
    return 0;
}
