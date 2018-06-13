//
// Created by Karolina on 05.05.2018.
//

//Zadanie 5 (bardzo często na kolokwium)
//Mamy mapę zatoki w postaci macierzy int M[n][m]
//int to głębokość zatoki w danym miejscu
//
//X 1 9 8 1 9
//3 3 4 2 2 1
//3 6 3 1 6 7
//
//T - głębokość zanużenia łodzi.
//Sprawdzić czy można dopłynąć z punktu (0,0) do (n-1,n-1).
//
//Złożoność O(nm).


bool Statek(int M[n][m], int n, int m, int T)
{
    set *** set = init(M,n,m);

    int D[][] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; //możliwe ruchy

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            if(M[x][y] > T)
            {
                for(int k = 0; k<4; k++)
                {
                    int x = D[k][0] + i;
                    int g = D[k][1] + j;

                    if(x>0 && x<n && y>0 && y<m)
                        if(M[x][y] > T)
                        {
                            Union(set[i][j], set[x][y]);
                        }

                }
            }
        }
    }
    bool r = (FindSet(set[0][0]) == FindSet(set[n-1][n-1]))
    deleteSet(set,n,r);
    return r;
}

set *** init(int n, int m)
{
    set *** tab = new set*[n];
    for(int i=0; i<n; i++)
    {
        tab[i] - new set*[n];  ////????
        for(int j=0; j<n; j++)
        {
            tab[i][j] = MakeSet();
        }
    }
    return tab;
}

