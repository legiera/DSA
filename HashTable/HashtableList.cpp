#include "stdafx.h"
#include <iostream>
using namespace std;

//struktury do metody listowej
struct Data {
	int value;
	Data * next;
};

struct HashTable {
	Data ** data;
	int size;
};

//funkcja haszuj¹ca
int getHash(Data * data)
{
	return  data->value;
}

//dodawanie w metodzie listowej
void insert(HashTable * HT, Data * data)
{
	//ustalanie indeksu 
	int x = getHash(data);
	int index = x% HT->size;

	//dodawanie na pocz¹tek listy o danym indeksie w tabeli
	data->next = HT->data[index];
	HT->data[index] = data;
	

}

//usuwanie w metodzie listowej
void remove(HashTable * HT, Data * data)
{
	//ustalanie indeksu 
	int x = getHash(data);
	int index = x% HT->size;

	//usuwanie
	Data * tmp = HT->data[index];	//poprzedni
	Data * tmp2 = tmp->next;		//aktualny

	if (tmp == data)
	{
		HT->data[index] = tmp->next;
		tmp->value = NULL;
	}
	else {
		while (tmp2->next != NULL)
		{
			if (tmp2 == data)
			{
				tmp = tmp2->next;
				tmp2->value = NULL;
			}
			else
			{
				tmp = tmp->next;
				tmp2 = tmp2->next;
			}
		}
	}
}

//szukanie metoda listowa
bool find(HashTable * HT, Data * data)
{
	//ustalanie indeksu
	int x = getHash(data);
	int index = x% HT->size;

	//wyszukiwanie wartoœci
	Data * tmp = HT->data[index];
	while (tmp != NULL)
	{
		if (tmp->value == data->value)	return true;
		else  tmp = tmp->next;
	}
	return false;
}

int main()
{
	//tworzenie HashTable
	HashTable * HT = new HashTable;
	HT->size = 4;
	HT->data = new Data *[HT->size];

	//ustawianie wszystkich pól na NULL 
	for (int i = 0; i < HT->size; i++)
		HT->data[i] = NULL;
	

	//Tworzenie danych
	Data * data = new Data;
	data->value = 1;
	data->next = NULL;

	Data * data1 = new Data;
	data1->value = 2;
	data1->next = NULL;

	Data * data2 = new Data;
	data2->value = 3;
	data2->next = NULL;

	Data * data3 = new Data;
	data3->value = 7;
	data3->next = NULL;

	Data * data4 = new Data;
	data4->value = 4;
	data4->next = NULL;

	insert(HT, data);
	insert(HT, data1);
	insert(HT, data2);
	insert(HT, data3);
	insert(HT, data4);

	remove(HT, data3);
	remove(HT, data);

	//wyswietlenie HashTable
	for (int i = 0; i < HT->size; i++)
	{
		if(HT->data[i] != NULL)
		{		
			cout << HT->data[i]->value<<"\t";
			if (HT->data[i]->next != NULL)
			{
				HT->data[i] = HT->data[i]->next;
				cout << HT->data[i]->value;
			}
			cout << endl;
		}
	}

	if (find(HT, data4)) cout << "got it!!" << endl;
	else cout << "couldn't find it ;c"<<endl;

	system("pause");
	return 0;
}