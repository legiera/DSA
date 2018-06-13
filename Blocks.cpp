//
// Created by Karolina on 05.05.2018.
//

//5. Mamy m dzieci:
//> c_1: w_1¹, ... w_n_1¹
//{ c_2: w_1², ... w_n_2²
//{ ...
//{ c_m: w_1^m, ... w_n_m^m
//Ile najmniej klocków dziecko c_1 musi zebrać aby wygrać?
//
//
//Każde z dzieci ma zestaw klocków różnej wysokości. Dzieci budują ze swoich klocków wieże. Wygrywa te które zbuduje najwyższą.
//Pierwsze dziecko jest złe i jak inne poszły na deser, to pozabierało klocki innym dzieciom.

// problem: niekoniecznie najwyższy klocek jest najlepszym wyborem
//lista najwyższych klocków dzieci
//klocek z najwyższej wieży ma większą wartość o różnicę między najwyższą wieżą a drugą najwyższą
//
//bierzemy czarodziejski poziom: taki żeby wszystkie wieże były niższe a nasza niekoniecznie wyższa
//zabieramy wszystkie najwyższe klocki z wież przekraczających poziom
//potem zabieramy najwyższe klocki z całej puli
//wyznaczanie poziomu: bierzemy poziomy po kolei
//    jeżeli możemy z każdej to minimum
//    jeżeli znajdziemy minimum i podniesiemy poprzeczkę to ilość klocków będzie wyższa
//    (narysował ~ -e^-x)