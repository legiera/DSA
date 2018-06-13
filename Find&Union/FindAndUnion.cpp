//https://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
#include <iostream>
using namespace std;

struct node {
	node * parent;
	int rank;			// maksymalna wysoko�� drzewa
	int val;			// warto�� elementu
};


node * MakeSet(int v)
{
	node * S = new node;
	S->parent = S;
	S->rank = 0;
	S->val = v;
	return S;
}


node * FindSet(node * x)
{
	if (x->parent != x)
	{
		node * y = FindSet(x->parent);
		x->parent = y;			// czyli przypinamy do korzenia ( wszystkie elementy po drodze te�) - korze� to reprezentant
		return y;			// zwracamy reprezentanta - y
	}
	else
		return x;			// je�li x jest w�asnym rodzicem, to jest reprezentantem (korzeniem)
}


void Union(node * x, node * y)
{
	node * rx = FindSet(x);			// reprezentanci
	node * ry = FindSet(y);

	if (rx->rank > ry->rank)
		ry->parent = rx;
	else							// czyli rx->rank <= ry->rank
	{
		rx->parent = ry;
		if (rx->rank == ry->rank)
			ry->rank++;
	}
}


void main()
{
	node * a = MakeSet(5);
	node * b = MakeSet(4);
	Union(a, b);
	node * c = FindSet(a);
	cout << c->val;
	int asd;
	cin >> asd;
}