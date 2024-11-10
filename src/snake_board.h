//
// Created by Michał Markuzel on 10/05/2023.
//

#ifndef SNAKE_SNAKE_BOARD_H
#define SNAKE_SNAKE_BOARD_H

#include <vector>
#include <iostream>
#include <cstdlib>


//===================== COORDINATES ========================
// - struktura przechowuje współrzędne x i y
// - przeciąża także operator "=" i "+", co ułatwia
// późniejszą implementację
//==========================================================
struct coordinates {
    int x;
    int y;

    bool operator==(coordinates a) {
        if (x == a.x && y == a.y)
            return true;
        else
            return false;
    }

    coordinates operator-(coordinates a) {
        a.x = x- a.x;
        a.y = y - a.y;
        return a;
    }
};

// enum do zawartości pola na planszy
enum board_content {
    APPLE, WALL, GRASS
};

//===================== SNAKE BOARD ========================
// - klasa przechowuje informacje o planszy oraz
// jej zawartości
// - posiada proste setter'y i getter'y
//==========================================================

class snake_board {
    const int WIDTH, HEIGHT;
    board_content board[100][100];

    // "apple" przechowuje aktualne współrzędne jebłka
    // (ulatwia to jego znalezienie)
    coordinates apple;
public:
    snake_board(int width, int height);

    // tworzy ściany, trawę i ustawia jedno jabłko na planszy
    void board_setup();

    // zwraca info o zawartości pola w tablicy
    board_content get_field_info(int x, int y);

    // gettery zwaracające wysokość i szerokość planszy
    int get_board_width() const;
    int get_board_height() const;

    // zwraca współrzędne jabłka
    coordinates get_apple_coord();

    // funkcje odpowiedzialne za tworzenie nowego jabłka
    // i usuwanie poprzeniego
    void grow_new_apple();
    void delete_old_apple(coordinates q);

    // sprawdza czy może postawić owoc
    bool can_it_grow(coordinates q) const;
};


#endif //SNAKE_SNAKE_BOARD_H
