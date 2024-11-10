//
// Created by Michał Markuzel on 10/05/2023.
//

#include "board_view.h"

board_view::board_view(snake_board &board, snake_body &snake, snake_logic &logic, score &scores) : board(board),
                                                                                                   snake(snake),
                                                                                                   logic(logic),
                                                                                                   scores(scores) {
    bool load;

    load = texture[0].loadFromFile("WALL.PNG");
    assert(load);
    wall.setTexture(texture[0]);

    load = texture[1].loadFromFile("APPLE.PNG");
    assert(load);
    apple.setTexture(texture[1]);

    load = texture[2].loadFromFile("GRASS.PNG");
    assert(load);
    grass.setTexture(texture[2]);

    load = texture[4].loadFromFile("HEAD_UP.PNG");
    assert(load);
    head[0].setTexture(texture[4]);

    load = texture[5].loadFromFile("HEAD_RIGHT.PNG");
    assert(load);
    head[1].setTexture(texture[5]);

    load = texture[6].loadFromFile("HEAD_DOWN.PNG");
    assert(load);
    head[2].setTexture(texture[6]);

    load = texture[7].loadFromFile("HEAD_LEFT.PNG");
    assert(load);
    head[3].setTexture(texture[7]);

    load = texture[8].loadFromFile("TAIL_UP.PNG");
    assert(load);
    tail[0].setTexture(texture[8]);

    load = texture[9].loadFromFile("TAIL_RIGHT.PNG");
    assert(load);
    tail[1].setTexture(texture[9]);

    load = texture[10].loadFromFile("TAIL_DOWN.PNG");
    assert(load);
    tail[2].setTexture(texture[10]);

    load = texture[11].loadFromFile("TAIL_LEFT.PNG");
    assert(load);
    tail[3].setTexture(texture[11]);

    load = texture[12].loadFromFile("TURN_UP_RIGHT.PNG");
    assert(load);
    body[0].setTexture(texture[12]);

    load = texture[13].loadFromFile("TURN_UP_LEFT.PNG");
    assert(load);
    body[3].setTexture(texture[13]);

    load = texture[14].loadFromFile("TURN_DOWN_RIGHT.PNG");
    assert(load);
    body[1].setTexture(texture[14]);

    load = texture[15].loadFromFile("TURN_DOWN_LEFT.PNG");
    assert(load);
    body[2].setTexture(texture[15]);

    load = texture[3].loadFromFile("BODY_HORISONTAL.PNG");
    assert(load);
    body[4].setTexture(texture[3]);

    load = texture[16].loadFromFile("BODY_VERTICAL.PNG");
    assert(load);
    body[5].setTexture(texture[16]);

    load = texture[17].loadFromFile("DEAD_UP.PNG");
    assert(load);
    dead_head[0].setTexture(texture[17]);

    load = texture[18].loadFromFile("DEAD_RIGHT.PNG");
    assert(load);
    dead_head[1].setTexture(texture[18]);

    load = texture[19].loadFromFile("DEAD_DOWN.PNG");
    assert(load);
    dead_head[2].setTexture(texture[19]);

    load = texture[25].loadFromFile("DEAD_LEFT.PNG");
    assert(load);
    dead_head[3].setTexture(texture[25]);

    load = texture[21].loadFromFile("EASY.PNG");
    assert(load);
    mode[0].setTexture(texture[21]);

    load = texture[22].loadFromFile("NORMAL.PNG");
    assert(load);
    mode[1].setTexture(texture[22]);

    load = texture[23].loadFromFile("HARD.PNG");
    assert(load);
    mode[2].setTexture(texture[23]);

    load = texture[24].loadFromFile("SCORE.PNG");
    assert(load);
    score_table.setTexture(texture[24]);

    load = font.loadFromFile("SQUARE.ttf");
    assert(load);
}

void board_view::draw(sf::RenderWindow &win) {
    draw_board(win);

    if (logic.get_game_state() == RUNNING || logic.get_game_state() == LOSE) {
        draw_head(win);

        draw_body(win);

        draw_tail(win);
    }
    if (logic.get_game_state() == START)
        draw_menu(win);

    if (logic.get_game_state() == LOSE)
        draw_score_table(win);
}

void board_view::generate_font(sf::Text &text)
{
    text.setFont(font);
    text.setCharacterSize(50);
    text.setColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setOrigin(text.getLocalBounds().width / 2., text.getLocalBounds().height / 2.);
}

void board_view::draw_score_table(sf::RenderWindow &win) {
    sf::Text text;
    generate_font(text);

    std::vector<int> temp = scores.get_score_table();

    // srodek tablicy - szekosc tablicy wynikow
    int x = board.get_board_width() * 25 / 2 - 180;
    // srodek tablicy - wysokosc tablicy wynikow
    int y = board.get_board_height() * 25 / 2 - 120;

    score_table.setPosition((float)x, (float)y);
    win.draw(score_table);

    // miejsce "zero" dla wyników
    x = board.get_board_width() * 25 / 2 - 165;
    y = board.get_board_height() * 25 / 2 + 5;
    int y_move = 0;
    int counter = 0;

    text.setString(std::to_string(snake.get_body_length()+1));
    text.setPosition(x + 255, y - 106);
    win.draw(text);

    text.setCharacterSize(20);

    for (int i = 0; i < 10; i++) {
        if (i % 3 == 0 && i > 2) {
            // odstep miedzy wynikami
            y_move += 85;
        }

        if (temp[i] == snake.get_body_length() + 1 && counter == 0) {
            text.setColor(sf::Color::Red);
            counter++;
        } else
            text.setColor(sf::Color::Black);

        std::string number = std::to_string(temp[i]);
        text.setString(std::to_string(i + 1) + ". " + number);

        // pozycja do numeru
        text.setPosition(x + y_move, y + (i % 3 * 30));

        win.draw(text);
    }
}

void board_view::draw_board(sf::RenderWindow &win) {
    for (int y = 0; y < board.get_board_height(); y++)
        for (int x = 0; x < board.get_board_width(); x++) {
            switch (board.get_field_info(x, y)) {
                case GRASS:
                    grass.setPosition(x * 25, y * 25);
                    win.draw(grass);
                    break;
                case WALL:
                    wall.setPosition(x * 25, y * 25);
                    win.draw(wall);
                    break;
                case APPLE:
                    apple.setPosition(x * 25, y * 25);
                    win.draw(apple);
                    break;
            }
        }
}

void board_view::draw_head(sf::RenderWindow &win) {
    coordinates q = snake.get_head_coordinates();
    coordinates x = snake.get_body_part_coordinates(0);

    if (q.x != 0 && q.x != board.get_board_width()-1 && q.y != 0 && q.y != board.get_board_height()-1)
        switch (orientacja_a_do_b(x, q)) {
            case UP:
                head[0].setPosition(q.x * 25, q.y * 25);
                win.draw(head[0]);
                break;
            case DOWN:
                head[2].setPosition(q.x * 25, q.y * 25);
                win.draw(head[2]);
                break;
            case RIGHT:
                head[1].setPosition(q.x * 25, q.y * 25);
                win.draw(head[1]);
                break;
            case LEFT:
                head[3].setPosition(q.x * 25, q.y * 25);
                win.draw(head[3]);
                break;
        }
    else {
        switch (orientacja_a_do_b(x, q)) {
            case UP:
                dead_head[0].setPosition(q.x * 25, q.y * 25);
                win.draw(dead_head[0]);
                break;
            case DOWN:
                dead_head[2].setPosition(q.x * 25, q.y * 25);
                win.draw(dead_head[2]);
                break;
            case RIGHT:
                dead_head[1].setPosition(q.x * 25, q.y * 25);
                win.draw(dead_head[1]);
                break;
            case LEFT:
                dead_head[3].setPosition(q.x * 25, q.y * 25);
                win.draw(dead_head[3]);
                break;
        }
    }
}


void board_view::draw_body(sf::RenderWindow &win) {
    coordinates q = snake.get_head_coordinates();

    for (int i = 0; i < snake.get_body_length() - 1; i++) {
        q = snake.get_body_part_coordinates(i);

        if (i + 1 < snake.get_body_length()) {
            int o = get_body_orientation(i);
            body[o].setPosition(q.x * 25, q.y * 25);
            win.draw(body[o]);
        }
    }
}

void board_view::draw_tail(sf::RenderWindow &win) {

    coordinates q, x;
    q = snake.get_body_part_coordinates(snake.get_body_length() - 1);
    if (snake.get_body_length() == 1)
        x = snake.get_head_coordinates();
    else
        x = snake.get_body_part_coordinates(snake.get_body_length() - 2);

    switch (orientacja_a_do_b(q, x)) {
        case UP:
            tail[0].setPosition(q.x * 25, q.y * 25);
            win.draw(tail[0]);
            break;
        case DOWN:
            tail[2].setPosition(q.x * 25, q.y * 25);
            win.draw(tail[2]);
            break;
        case LEFT:
            tail[3].setPosition(q.x * 25, q.y * 25);
            win.draw(tail[3]);
            break;
        case RIGHT:
            tail[1].setPosition(q.x * 25, q.y * 25);
            win.draw(tail[1]);
            break;
    }
}

direction orientacja_a_do_b(coordinates a, coordinates b) {
    if (a.x == b.x && a.y > b.y)
        return UP;

    if (a.x == b.x && a.y < b.y)
        return DOWN;

    if (a.x < b.x && a.y == b.y)
        return RIGHT;

    if (a.x > b.x && a.y == b.y)
        return LEFT;

    return UP;
}

int board_view::get_body_orientation(int i) {
    coordinates a, b, c;

    if (i == 0)
        a = snake.get_head_coordinates();
    else
        a = snake.get_body_part_coordinates(i - 1);

    b = snake.get_body_part_coordinates(i);
    c = snake.get_body_part_coordinates(i + 1);

    b.x = b.x - 1;
    b.y = b.y - 1;

    a = a - b;
    c = c - b;

    int matrix[3][3];

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            matrix[i][j] = 0;

    matrix[a.x][a.y] = 1;
    matrix[c.x][c.y] = 1;

    // 5 - połączenie pionowe
    if (matrix[1][0] == 1 && matrix[1][2] == 1)
        return 5;
    // 2 - połączenie dołu z lewą
    if (matrix[0][1] == 1 && matrix[1][2] == 1)
        return 2;
    // 1 - połączenie prawej z dołem
    if (matrix[2][1] == 1 && matrix[1][2] == 1)
        return 1;
    // 3 - połączenie lewa z górą
    if (matrix[0][1] == 1 && matrix[1][0] == 1)
        return 3;
    // 0 - połączenie góra z prawą
    if (matrix[1][0] == 1 && matrix[2][1] == 1)
        return 0;
    // 4 - połączenie poziome
    if (matrix[0][1] == 1 && matrix[2][1] == 1)
        return 4;

    return 0;
}

void board_view::draw_menu(sf::RenderWindow &win) {
    // środek planszy - szerokosc menu
    float x = (float) board.get_board_width() * 25 / 2 - 62;
    // środek planszy - wysokosc menu
    float y = (float) board.get_board_height() * 25 / 2 - 31;

    mode[0].setPosition(x, y - 100);
    win.draw(mode[0]);
    mode[1].setPosition(x, y);
    win.draw(mode[1]);
    mode[2].setPosition(x, y + 100);
    win.draw(mode[2]);
}
