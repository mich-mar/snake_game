//
// Created by Michał Markuzel on 10/05/2023.
//

#include "snake_board.h"


void snake_board::board_setup() {

    for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < HEIGHT; y++)
            board[x][y] = GRASS;

    for (int x = 0; x < WIDTH; x++)
        board[x][0] = WALL;

    for (int x = 0; x < WIDTH; x++)
        board[x][HEIGHT - 1] = WALL;

    for (int y = 0; y < HEIGHT; y++)
        board[0][y] = WALL;

    for (int y = 0; y < HEIGHT; y++)
        board[WIDTH - 1][y] = WALL;

    grow_new_apple();

}

snake_board::snake_board(int width, int height) : WIDTH(width), HEIGHT(height) {
    board_setup();
};

board_content snake_board::get_field_info(int x, int y) {
    switch (board[x][y]) {
        case GRASS:
            return GRASS;
            break;
        case WALL:
            return WALL;
            break;
        case APPLE:
            return APPLE;
            break;
    }
}

int snake_board::get_board_width() const{
    return WIDTH;
}

void snake_board::delete_old_apple(coordinates q) {
    board[q.x][q.y] = GRASS;
}

int snake_board::get_board_height() const{
    return HEIGHT;
}

coordinates snake_board::get_apple_coord() {
    return apple;
}

void snake_board::grow_new_apple() {

    srand((unsigned) time(NULL));

    coordinates q;
    int apple_counter = 0;

    while (apple_counter == 0) {
        q.x = rand() % WIDTH;
        q.y = rand() % HEIGHT;

        if (can_it_grow(q)) {
            board[q.x][q.y] = APPLE;
            apple_counter++;
            apple = q;
        }
    }
}

bool snake_board::can_it_grow(coordinates q) const {
    if (q.x != 0 && q.x != WIDTH - 1 && q.y != 0 && q.y != HEIGHT - 1)
        if (q.x != WIDTH / 2 && q.y != HEIGHT / 2)
            return true;

    return false;
}
