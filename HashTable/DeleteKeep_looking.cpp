//
// Created by Karolina on 09.05.2018.
//

#include <iostream>
using namespace std;

//enum status {1,2,3};

struct HT{
    int *status;
    int size;
    int *table;
};
int gethash(HT *ht,int key){
    return (key%ht->size);
}
void insert(HT *ht, int key){
    int l=gethash(ht,key);
    int i=0;
    while(ht->size>i){

        if(ht->status[l]==2 || ht->status[l]== 1) {
            ht->table[l]=key;
            ht->status[l]=3;
            return;
        }
        l=(l+1)%ht->size;
        i++;
    }
    cout<<"Nie dodano"<<endl;
    return;
}
int find(HT *ht, int key){
    int l=gethash(ht,key);
    int i=0;
    while(ht->size>i){
        if(ht->status[l]==1) return -1;
        if(ht->status[l]==3 && ht->table[l]==key) return l;

            l = (l + 1) % ht->size;
            i++;

    }
}
void deleted(HT *ht, int key){
    int f=find(ht, key);
    if(f==-1) return;
    else{
        ht->table[f]=-1;
        ht->status[f]=2;
        return;
    }
}
void fix(HT* ht,int ind){

    int i=ind+1;
    while(ht->size>i) {
        int p = gethash(ht, ht->table[i]);
        if (ind >= p && ht->status[i] == 3) {
            ht->table[ind] = ht->table[i];
            ht->status[ind] = 3;
            ht->status[i] = 2;
            ht->table[i] = -1;


            ind = i;
            i++;
        } else i++;

    }
    return;

}

void deleteKeep(HT *ht){
    for(int i=0;i<ht->size;i++){
        if(ht->status[i]==2)
            fix(ht,i);
    }
}


int main() {
    //tworzenie HashTable
    HT *ht = new HT;
    ht->size = 8;
    ht->table = new int [ht->size];
    ht->status = new int [ht->size];

    //ustawianie wszystkich pól na NULL
    for (int i = 0; i < ht->size; i++) {
        ht->table[i] = -1;
        ht->status[i]=1;
    }
    insert(ht,5);
    insert(ht,3);
    insert(ht,1);
    insert(ht,1);
    insert(ht,2);
    insert(ht,12);
    insert(ht,18);
    insert(ht,7);

    for (int i = 0; i < ht->size; i++) {
        cout<<ht->table[i]<<" ";

    }
    deleted(ht,1);
    //cout<<find(ht,12)<<endl;
    deleted(ht,12);
    cout<<endl;
    deleteKeep(ht);
    for (int i = 0; i < ht->size; i++) {
       if(ht->status[i]==2) cout<<"nie działa"<<endl;
        cout<<ht->table[i]<<" ";
    }

}