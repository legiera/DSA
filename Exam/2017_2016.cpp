//
// Created by Karolina on 03.05.2018.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//I termin

//[2pkt.] Zadanie 2. Dana jest SkipLista przechowująca liczby z przedziału (0,1). Proszę opisać (bez
//  implementacji) algorytm, który z takiej SkipListy usuwa wszystkie liczby z zadanego przedziału (x, y)
//        (gdzie 0 < x < y < 1). Proszę oszacować złożoność obliczeniową zaproponowanego algorytmu jako funkcję
//liczby n elementów w SkipLiście (przed operacją usuwania) oraz liczby d elementów, które zostaną
//        usunięte. Proszę uzasadnić przedstawione oszacowanie złożoności. Algorytm powinien być możliwie jak
//        najszybszy. Ocenie podlega poprawność i efektywność algorytmu (1pkt) oraz poprawność oszacowania
//        złożoności czasowej (1pkt).

//Złożoność O(logn + d)
//Wyszukuje wartość x i zapamiętuję poprzednika, wyszukuje następnika y i przepinam i usuwam za pomocą remove 

//[2pkt.] Zadanie 4. Dany jest graf G = (V, E), którego wierzchołki reprezentują punkty nawigacyjne nad
//        Bajtocją, a krawędzie reprezentują korytarze powietrzne między tymi punktami. Każdy korytarz
//powietrzny ei ∈ E powiązany jest z optymalnym pułapem przelotu pi ∈ N (wyrażonym w metrach).
//Przepisy dopuszczają przelot danym korytarzem jeśli pułap samolotu różni się od optymalnego najwyżej o
//t metrów. Proszę zaproponować algorytm (bez implementacji), który sprawdza czy istnieje możliwość
//        przelotu z zadanego punktu x ∈ V do zadanego punktu y ∈ V w taki sposób, żeby samolot nigdy nie
//        zmieniał pułapu. Algorytm powinien być poprawny i możliwie jak najszybszy. Proszę oszacować jego
//        złożoność czasową.

//III termin
//Rozważmy tablice haszujące z adresowaniem otwartym i liniowym rozwiazywaniem konfliktów. Zakładamy że
//sprawdzenie czy dany ele należy do takiej tablicy zajmuje czas stały. Mamy dane dwie tablice A,B obie
//majace n pół i przechowujace k elementów (k<=n) Przy standardowej implementacji sprawdzenie, czy takie
//        tablice zawierają dokładnie takie same elementy zajmuje czas O(n). Proszę zaproponować rozszerzenie
//tej struktury danych tak aby nie pogorszyła się złożoność operacji wstawiania, usuwania i sprawdzania
//przynależnosci elementów ale by dało się sprawdzać czy dwie tablice mają dokładnie takie same elem w
//czasie O(k), Proszę opisać alg porównywania tablic.

//Rozwiazanie (2/2pkt.):
//Tworzymy dodatkowe tablice C[] i D[] o tym samym rozmiarze co dane tablice z haszowaniem A[] i B[]
//        (tzn. obydwie po n-elementow).
//Przegladamy tablice z haszowanem A[] i inicjalizujemy tablice C[] wpisujac do jej elementow, pod
//kolejnymi indeksami (poczawszy do elementu pod indeksem 0), numer indeksu pod ktorym, w tablicy
//        z haszowaniem A[], znajduje sie kolejna liczba.
//Analogicznie postepujemy z tablica z haszowaniem B[] i utworzona przez nas wczesniej tablica C[].
//W ten sposob tablice C[] i D[] beda wypelnione od indeksu 0 do k-1 wlacznie.
//
//Podczas przegladania tablic z haszowaniem A[] i B[] kazdy z jej elementow rozszerzamy dodajac
//do struktury go opisujacej pole 'indeks', gdzie zapisujemy nr indeksu elementu tablicy
//wczesniej utworzonej (tablicy C[] w przypadku tablicy A[] i tablicy D[] w przypadku tablicy B[])
//w ktorym zapisujemy wlasnie nr indeksu z tablicy z haszowaniem.
//
//Jesli wstawiamy nowy element do tablicy z haszowaniem...
//
//        Jesli usuwamy element z tablicy haszujacej, to usuwamy jednoczesnie pole w zwyklej tablicy...
//
//
//        Algorytm porownywania tablic:
//1. Tworzymy tablice C[] i D[] oraz rozszerzamy struktury opisujace elementy tablic z haszowaniem A[] i B[]
//w wyzej opisany sposob.
//2. Przeszukujemy tablice C[] oraz D[] iterujac po kolejnych indeksach i (i od 0 do k-1). Za kazdym razem (dla kazdego i)
//patrzymy pod odpowiedni indeks w tablicach A[] i B[] i porownujemy czy elementy te maja taka sama wartosc.
//3. Jesli odpowiadajace sobie elementy z tablic A[] i B[] dla jakiegos i nie beda mialy rownych wartosci przerywamy
//        algorytm i zwracamy komunikat, ze tablice A[] i B[] nie maja dokladnie takich samych elementow.
//Jezeli dla kazdego i odpowiadajace sobie elementy z tablic A[] i B[] beda mialy rowne wartosci, to
//po przeiterowaniu po k-razy po tablicach C[] i D[] algorytm zwraca komunikat, ze maja dokladnie takie same elementy.
//
//Zlozonosc czasowa algorytmu porownywania tablic A[] i B[] wyniesie wowczas O(k), bo po k elementow (rozlokowanych
//pod indeksami od 0 do k-1) zawieraja tablice C[] i D[], ktore musimy przegladnac.
