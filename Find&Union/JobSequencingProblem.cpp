//
// Created by Karolina on 05.05.2018.
//
//
//Given a set of n jobs where each job i has a deadline di >=1 and profit pi>=0. Only one job can be scheduled
//at a time. Each job takes 1 unit of time to complete. We earn the profit if and
//only if the job is completed by its deadline. The task is to find the subset of jobs that maximizes profit.

//https://www.geeksforgeeks.org/job-sequencing-using-disjoint-set-union/
#include<iostream>
using namespace std;

struct set{
    set *parent;
    int profit_sum;
    int current_deadline;
    int size;
};

struct job{
    int d; //deadline
    int p; //profit
};

set * MakeSet(job x){
    set *tmp=new set;
    tmp->parent=tmp;
    tmp->profit_sum= x.p;
    tmp->current_deadline=x.d;
    tmp->size=1;

    return tmp;
}
set *FindSet(set *x){
    if(x->parent!=x)
        return x->parent=FindSet(x->parent);
    return x;
}

void Union(set *x, set *y){
    x=FindSet(x);
    y=FindSet(y);
    if(x==y) return;

    if(x->size>y->size){
        y->parent=x;
        x->size+=y->size;
        x->profit_sum+=y->profit_sum;
        if(x->current_deadline<y->current_deadline)
            x->current_deadline=y->current_deadline;
    }
    else {
        x->parent=y;
        y->size+=x->size;
        y->profit_sum+=x->profit_sum;
        if(x->current_deadline > y->current_deadline)
            y->current_deadline=x->current_deadline;
    }

}
void maxProfit(job *tab, int n){
   set *Jobs[n];
    //posortować tab po deadlinach malejąco
    for(int i=0;i<n;i++)
        Jobs[i]=MakeSet(tab[i]);

    for(int i=0;i<n ;i++){
        for(int j=0;j<n;j++)
        if(i!=j && (tab[i].d<tab[j].d ))
            Union(Jobs[i],Jobs[j]);
    }
    int maxprofit=0;
    set *p;
    set *d;
    for(int i=0;i<n;i++){
        d=FindSet(Jobs[i]);
        if(maxprofit<d->profit_sum) {
            maxprofit=d->profit_sum;
            p=d;
        }
    }
    cout<<maxprofit<<" "<<p->parent<<endl;
}
//nie wiem czy działa dobrze, złożoność kwadratowa
int main()
{
    int n=4;
    job arr[] =  { {  2, 100 }, {  1, 27 },
                   {  2, 25 },  {  1, 19 },
                   {  3, 15 } };
    cout << "Following jobs need to be "
         << "executed for maximum profit\n";
    maxProfit(arr, n);
    return 0;
    return 0;
}