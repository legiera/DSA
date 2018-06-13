//
// Created by Karolina on 03.05.2018.
//

//Dana jest następująca struktura opisująca drzewo:
//
//struct Tree{
//    Tree *parent;           // rodzic, lub NULL jeśli to korzen
//    Tree *left, *right;     // lewe i prawe dziecko
//    int w_left, w_right;    // wagi krawędzi do lewego i do prawego dziecka (dodatnie)
//};
//Proszę opisać (bez implementacji) możliwie jak najszybszy algorytm, który mając na wejściu 
//drzewo opisane przez strukturę Tree znajduje długość najdłuższej ścieżki między dwoma węzłami
// drzewa (prosta ścieżka to taka, która nie odwiedza żadnego węzła więcej niż raz).
//
//(Na potrzeby algorytmu mogą państwo uzupełnić strukturę Tree o dalsze pola.)

struct Tree{
	Tree *parent; //rodzic, lub NULL jeśli to korzeń
	Tree *left, *right; //lewe I prawe dziecko
	int w_left, w_right; //wagi krawędzi do lewego i do prawego dziecka (dodatnie)
	int longest_path, longest_path_to_root;	//najdluzsza sciezka w poddrzewie(lacznie z tym wezlem),
	// najdluzsza sciezka do tego wezla
};

//W kazdym wezle uzupelniam informacje o najdluzszej sciezce prowadzacej do tego wezla,
//		oraz najdluzszej sciezce w drzewie zakorzenionym w tym wezle.

