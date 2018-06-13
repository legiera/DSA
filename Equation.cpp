//
// Created by Karolina on 05.05.2018.
//

/* Mamy tablicę float x[N]. W tej tablicy jest zapisane N wartości.
Stwórz tablicę float y[N] takiej, że y[i] = 1/x[i] * Π(j=0,n-1) x[j].
haczyk: nie wolno używać dzielenia i trzeba jak najszybciej.

  1   2   3   4   5   6
  1   2   6  18  70 420 - początki
720 720 360 120  30   6 - końce
takie dobre dla samogłosek z jedną literką B - chcemy jedną pomocniczą:
w tablicy początków robimy to samo
jedziemy od końca i mnożymy od razu w tablicy początków
w sumie nie potrzeba tablicy początków, można od razu w wynikach
=> czyli potrzebujemy tylko jedną zmienną float
*/