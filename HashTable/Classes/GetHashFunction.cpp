//
// Created by Karolina on 03.05.2018.
//

//#include "stdafx.h"
#include <iostream>
using namespace std;

//Zadanie 3
//Wymyślić "dobrą" funkcję haszującą dla struktury

struct Data
{
char* firstname;
char* lastname;
int age;
};
//__________

int hash(Data * x)
{
    int h;
    int i = 0;
    int s = x-> strlen(x->firstname);

    for (i; i < s; i++)
        h += (i++)*x->firstname[i];

    s = strlen(x-> lastname);

    for(int j=0; j<s; j++, s++)
        h += (j++)*x->lastname[j];

    h *= x->age;

    return h;

}


