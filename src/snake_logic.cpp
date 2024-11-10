//
// Created by Michał Markuzel on 10/05/2023.
//

#include "snake_logic.h"

snake_logic::snake_logic(snake_body &snake, snake_board &board, score &scores) : snake(snake), board(board), scores(scores){
    level = CHOOSE;
    state = START;
    actual_direction = LEFT;
}


void snake_logic::handle_event(sf::Event &event, sf::RenderWindow &win) {
    if (state == RUNNING)
        handle_gameplay(event);
    if (state == START)
        handle_menu(event, win);
}

void snake_logic::handle_gameplay(sf::Event &event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        if (actual_direction != RIGHT)
            actual_direction = LEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        if (actual_direction != LEFT)
            actual_direction = RIGHT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        if (actual_direction != DOWN)
            actual_direction = UP;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        if (actual_direction != UP)
            actual_direction = DOWN;
}

void snake_logic::handle_menu(sf::Event &event, sf::RenderWindow &win) {
    sf::Vector2u size = win.getSize();
    float x_scale = (float) size.x/(board.get_board_width() * 25);
    float y_scale = (float) (size.y+1)/(board.get_board_height() * 25);
    std::cout << "Wysokość: " << y_scale << "Szerokość: " << x_scale << std::endl;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        float q_x = event.mouseButton.x;
        float q_y = event.mouseButton.y;
        // 124x62
        float x = (float)(board.get_board_width() * 25 / 2 - 62);
        float y = (float)(board.get_board_height() * 25 / 2 - 31);

        if (q_y >= (y - 100)*y_scale && q_y <= (y + 224)*y_scale && q_x >= x*x_scale && q_x <= (x + 124)*x_scale) {
            if (q_y < (y - 38)*y_scale) {
                run_game(EASY);
            } else if (q_y > y*y_scale && q_y < (y + 62)*y_scale) {
                run_game(NORMAL);
            } else if (q_y > (y + 100)*y_scale) {
                run_game(HARD);
            }
            //usleep(0.5 * 1000000);
        }
    }
}

void snake_logic::gameplay() {
    if (state == RUNNING) {
        coordinates q;
        q = snake.get_head_coordinates();

        if (is_snake_on_wall(q)) {
            state = LOSE;
            scores.add_new_score(snake.get_body_length()+1);
            scores.sort();
            scores.save_file();
        } else if (is_snake_on_snake(q)) {
            state = LOSE;
            scores.add_new_score(snake.get_body_length()+1);
            scores.sort();
            scores.save_file();
        } else {
            if (snake.get_head_coordinates() == board.get_apple_coord()) {
                snake.make_snake_longer(q, actual_direction);
                board.grow_new_apple();
                board.delete_old_apple(q);
            } else {
                snake.move_whole_body(q, actual_direction);
            }
        }
    }
}


bool snake_logic::is_snake_on_wall(coordinates q) {
    if (q.x == 0 || q.x == board.get_board_width() - 1 || q.y == 0 || q.y == board.get_board_height() - 1)
        return true;
    else
        return false;
}

bool snake_logic::is_snake_on_snake(coordinates q) {
    for (int i = 0; i < snake.get_body_length() - 1; i++)
        if (snake.get_body_part_coordinates(i) == q)
            return true;
    return false;
}

game_state snake_logic::get_game_state() {
    return state;
}

void snake_logic::run_game(game_level level) {
    this->level = level;
    state = RUNNING;
}

float snake_logic::get_game_lvl() {
    switch (level) {
        case EASY:
            return 1.5;
            break;
        case NORMAL:
            return 1.25;
            break;
        case HARD:
            return 1;
            break;
        case CHOOSE:
            return 0.001;
            break;
    }
    return 2;
}
