//
// Created by Michał Markuzel on 10/05/2023.
//

#ifndef SNAKE_BOARD_VIEW_H
#define SNAKE_BOARD_VIEW_H
#include "snake_body.h"
#include "snake_logic.h"
#include "score.h"
#include <SFML/Graphics.hpp>
#include <cassert>

// funkcja zwracająca orientacje względem dwóch współrzędnych
direction orientacja_a_do_b(coordinates a, coordinates b);



//===================== SNAKE BOARD ========================
// - klasa przechowuje informacje o planszy oraz
// jej zawartości
// - posiada proste setter'y i getter'y
//==========================================================

class board_view {
    snake_board &board;
    snake_body &snake;
    snake_logic &logic;
    score &scores;

    // zmienne do wczytywania textur
    sf::Sprite apple;
    sf::Sprite grass;
    sf::Sprite wall;
    sf::Sprite head[4];
    sf::Sprite body[6];
    sf::Sprite dead_head[4];
    sf::Sprite tail[4];
    sf::Sprite mode[3];
    sf::Sprite score_table;
    sf::Font font;

    // buffor do wczytywania textur
    sf::Texture texture[100];

public:
    board_view(snake_board &board, snake_body &snake, snake_logic &logic, score &scores);

    // rysuje wszystko na ekranie
    void draw(sf::RenderWindow &win);

    // rysuje ogon, ciało i głowę węża
    void draw_body(sf::RenderWindow &win);
    void draw_tail(sf::RenderWindow &win);
    void draw_head(sf::RenderWindow &win);

    // rysuje plansze
    void draw_board(sf::RenderWindow &win);

    // rysuje menu wyboru poziomu trudnosći
    void draw_menu(sf::RenderWindow &win);

    // rysuje tablice z wynikami
    void draw_score_table(sf::RenderWindow &win);

    // funkcja sprawdzająca orientacje tekstur
    // (kierunek głowy, ogona, skrętów i prostych części węża)
    int get_body_orientation(int i);

    // ustawia czcionkę
    void generate_font(sf::Text &text);
};


#endif //SNAKE_BOARD_VIEW_H
