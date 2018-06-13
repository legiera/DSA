//
// Created by Karolina on 05.05.2018.
//

//Given a boolean 2D matrix, find the number of islands.
//
//A group of connected 1s forms an island. For example, the below matrix contains 5 islands
//
//{1, 1, 0, 0, 0},
//{0, 1, 0, 0, 1},
//{1, 0, 0, 1, 1},
//{0, 0, 0, 0, 0},
//{1, 0, 1, 0, 1}
//A cell in 2D matrix can be connected to 8 neighbors.

//https://www.geeksforgeeks.org/find-the-number-of-islands-set-2-using-disjoint-set/
#include<iostream>
using namespace std;
struct Node{
    Node *parent;
    int rank;
    int size;
    int idx;
    int idy;

};

Node * MakeSet(int val,int indx,int indy){
    Node *tmp=new Node;
    tmp->parent=tmp;
    tmp->idx=indx;
    tmp->idy=indy;
    tmp->rank=0;
    tmp->size=1;
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
        y->idx=x->idx;
        y->idy=x->idy;
        x->size+=y->size;
        x->rank+=y->rank;
    }
    else{
        x->parent=y;
        x->idx=y->idx;
        x->idy=y->idy;
        y->size+=x->size;
        y->rank+=x->rank;
        if(x->rank==y->rank)
            y->rank+=1;
    }
}
const int N=5;
int numberOfIslands(int tab[N][N], int n){
    Node *Island[n][n];
    for(int i=0;i<n ;i++)
        for(int j=0;j<n;j++)
        Island[i][j]=MakeSet(tab[i][j],i,j);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(tab[i][j]==1){
              
                if (j+1 < n && tab[i][j+1]==1)
                    Union(Island[i][j],Island[i][j+1]);
                if (j-1 >= 0 && tab[i][j-1]==1)
                    Union(Island[i][j], Island[i][j-1]);
                if (i+1 < n && tab[i+1][j]==1)
                    Union(Island[i][j], Island[i+1][j]);
                if (i-1 >= 0 && tab[i-1][j]==1)
                    Union(Island[i][j], Island[i-1][j]);
                if (j+1<n && i+1<n && tab[i+1][j+1]==1)
                    Union(Island[i][j], Island[i+1][j+1]);
                if (j+1<n && i-1>=0 && tab[i-1][j+1]==1)
                    Union(Island[i][j], Island[i-1][j+1]);
                if (j-1>=0 && i+1<n && tab[i+1][j-1]==1)
                    Union(Island[i][j], Island[i+1][j-1]);
                if (j-1>=0 && i-1>=0 && tab[i-1][j-1]==1)
                    Union(Island[i][j], Island[i-1][j-1]);

            }

    int c[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            c[i][j]=0;
    //nie wiem jak to działa i też jest kwadratowa
    int numberOfIslands = 0;
    for (int j=0; j<n; j++)
    {
        for (int k=0; k<n; k++)
        {
            if (tab[j][k]==1)
            {

                 Node *x = FindSet(Island[j][k]);

                // If frequency of set is 0,
                // increment numberOfIslands
                if (c[x->idx][x->idy]==0)
                {
                    numberOfIslands++;
                    c[x->idx][x->idy]++;
                }

                else
                    c[x->idx][x->idy]++;
            }
        }
    }
    return numberOfIslands;

}
int main() {
    int a[N][N]=         {{1, 1, 0, 0, 0},
                         {0, 1, 0, 0, 1},
                         {1, 0, 0, 1, 1},
                         {0, 0, 0, 0, 0},
                         {1, 0, 1, 0, 1}
    };
   cout<<"Number of Islands is: " <<numberOfIslands(a,5);
}