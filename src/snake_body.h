//
// Created by Michał Markuzel on 10/05/2023.
//

#ifndef SNAKE_SNAKE_BODY_H
#define SNAKE_SNAKE_BODY_H
#include "snake_board.h"

// enum do ustawienia kierunku w którym  ma iść wąż
enum direction {UP, DOWN, LEFT, RIGHT};



//===================== SNAKE BODY ========================
// - klasa przechowuje informacje o planszy oraz
// jej zawartości
// - posiada proste setter'y i getter'y
//==========================================================

class snake_body {
    // vektor przechowujący współrzędne każdej części ciała
    std::vector<coordinates> body;

    coordinates head;

    const int width;
    const int height;

public:
    snake_body(int width, int height);

    // zwraca współrzędne głowy węża
    coordinates get_head_coordinates();

    // przesuwa głowę węża zależnie od kierunku
    void change_head_coordinates(direction d);

    // wydłuża węża o jedną długość
    void make_snake_longer(coordinates q, direction d);

    // zwraca współrzędne jednej części ciała węża
    coordinates get_body_part_coordinates(int body_index);

    // zwraca długość węża
    int get_body_length();

    // przesuwa głowę węża na podane współrzędne i całe ciało za nim
    void move_whole_body(coordinates q, direction d);
};


#endif //SNAKE_SNAKE_BODY_H
