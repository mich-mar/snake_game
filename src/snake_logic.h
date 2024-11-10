//
// Created by Michał Markuzel on 10/05/2023.
//

#ifndef SNAKE_SNAKE_LOGIC_H
#define SNAKE_SNAKE_LOGIC_H

#include "snake_board.h"
#include "snake_body.h"
#include <SFML/Graphics.hpp>
#include "score.h"
#include <unistd.h>


enum game_state {
    START, RUNNING, LOSE
};

enum game_level {
    EASY, NORMAL, HARD, CHOOSE
};


//===================== SNAKE LOGIC ========================
// - klasa przechowuje informacje o planszy, wężu i wynikach
// - ustala poziom trudności
// - przechowuje informacje o stanie gry i zmienia go
// - podejmuje decyzje na podstawie eventów
//==========================================================

class snake_logic {
    snake_body &snake;
    snake_board &board;
    score &scores;

    game_state state;
    game_level level;

    // przechowuje informacje o aktualnym kierunku węża
    direction actual_direction;
public:
    snake_logic(snake_body &snake, snake_board &board, score &scores);

    // podejmuje działania ze względu na event
    void handle_event(sf::Event &event, sf::RenderWindow &win);

    // funkcje podejmujące decyzje na podstawie eventów
    void gameplay();
    void handle_gameplay(sf::Event &event);
    void handle_menu(sf::Event &event, sf::RenderWindow &win);

    // pomocnicze funkcje sprawdzające, czy gracz przegra przy danym ruchu
    bool is_snake_on_wall(coordinates q);
    bool is_snake_on_snake(coordinates q);

    // getter zwracający stan gry
    game_state get_game_state();

    // funkcja uruchamiająca grę z danym poziomem trudności
    void run_game(game_level level);

    // getter zwaracający poziom trudności, potrzebny do opóźnienia
    float get_game_lvl();

    direction get_direction();
};


#endif //SNAKE_SNAKE_LOGIC_H
