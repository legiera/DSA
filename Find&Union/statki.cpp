#include <iostream>
using namespace std;

struct Cyclist{
	int id, id_next;
};

struct set{
	set * parent;
	Cyclist cyclist;
	int rank;
};

//make set, find, union, is

set * makeSet(Cyclist cyclist){
	
	set * tmp = new set;
	tmp->rank = 1;
	tmp->cyclist = cyclist;
	tmp->parent = tmp;
	
	return tmp;	
}

set * findSet(set * tmp){
	if(tmp->parent != tmp){
		return  tmp->parent = findSet(tmp->parent);
	}
	
	return tmp;
}

void unionSet(set * x, set * y){
	
	x = findSet(x);
	y = findSet(y);
	
	if(x == y) return;
	
    y->parent=x;
    x->rank += y->rank;
	
}
/*
int countPossible(bool A[5][4], int n, int m, int x, int y){
	
	set * bay[n][m];
	int count = 0;
	
	for(int i = 0; i< n; i++){
		for(int j = 0; j<m; j++){
			bay[i][j] = makeSet(A[i][j]);
		}
	}
	
	for(int i = 0; i< n; i++){
		for(int j = 0; j<m; j++){
			
			if(A[i][j]){
				
				if( i + 1 < n && A[i+1][j]){
					unionSet(bay[i][j], bay[i+1][j]);
				}
					
					
				if( j + 1 < m && A[i][j+1])
					unionSet(bay[i][j], bay[i][j+1]);
				
					
			}
						
		}
	}
	
	set * position = findSet(bay[x][y]);
	
	return position->rank;	
}*/

int smallestGroup(Cyclist cyclist[], int n){
	
	set * tab[100]; //przy za�o�eniu �e numery s� od 1 do 100
	
	for(int i = 0; i < n; i++){
		tab[cyclist[i].id]  = makeSet(cyclist[i]);

	}
	
	for(int i = 0; i< n; i++){
		if(cyclist[i].id_next != -1)
			unionSet(tab[cyclist[i].id], tab[cyclist[i].id_next]);
	}
	
	
	int min = n+1;
	int tmp = 0;
	for(int i = 0; i<n; i++){
		tmp = findSet(tab[cyclist[i].id])->rank;
		if(tmp < min) min = tmp;
	}
	
	return min;
	
}

Cyclist * create(int id, int id_next){
	
	Cyclist * tmp = new Cyclist;
	tmp->id = id;
	tmp->id_next = id_next;
	
	return tmp;
}


int main(){
	
	Cyclist cyclist[10];
	cyclist[0].id = 78;
	cyclist[0].id_next = 34;
	cyclist[1].id = 99;
	cyclist[1].id_next = -1;
	cyclist[2].id = 19;
	cyclist[2].id_next = 25;
	cyclist[3].id = 42;
	cyclist[3].id_next = -1;
	cyclist[4].id = 77;
	cyclist[4].id_next = 39;
	cyclist[5].id = 34;
	cyclist[5].id_next = 56;
	cyclist[6].id = 67;
	cyclist[6].id_next = 99;
	cyclist[7].id = 39;
	cyclist[7].id_next = 19;
	cyclist[8].id = 25;
	cyclist[8].id_next = 42;
	cyclist[9].id = 56;
	cyclist[9].id_next = 77;
	
	
	cout<<smallestGroup(cyclist,10);
	
	
	
	/*int A[5][4] = {
	{5,4,1,3},
	{0,4,2,1},
	{3,5,5,4},
	{1,4,3,5},
	{0,2,5,5}};
	
	if(canEnter(A,5,4,3)) cout<<"Hurray!"<<endl;
	else cout<<"dupa";
	
	bool A[5][4]{
	{1,1,0,1},
	{0,1,0,1},
	{0,0,1,0},
	{1,1,0,1},
	{0,1,1,1}};
	
	cout<<countPossible(A,5,4,0,3);*/
	
	return 0;
}
