//
// Created by Michał Markuzel on 12/05/2023.
//

#ifndef SNAKE_SCORE_H
#define SNAKE_SCORE_H
#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>




//======================= SCORE ============================
// - klasa przechowuje wyniki w grze
// - odczytuje poprzednią tabelę z pliku scores.txt
// - dodaje nowy wynik jeśli jest w pierwszej dziesiątce
// i sortuje tabelę
//==========================================================

class score {
    // strumienie do odczytu i zapisu plików
    std::ofstream file_write;
    std::ifstream file_read;

    // wektor z wynikami
    std::vector<int> value;

    // nazwa pliku
    const std::string file_name;
public:
    // konstruktor wczytuje dane z pliku
    score(std::string file_name);

    // funkcja do sortowania
    void sort();

    // funkcja pomocnicza do sortowania
    void swap(int i, int j);

    // funkcja dodająca nowy wynik do tabeli
    void add_new_score(int i);

    // getter zwracający vector z wynikami
    std::vector<int> get_score_table();

    // funkcja zapisująca plik
    void save_file();
};


#endif //SNAKE_SCORE_H
