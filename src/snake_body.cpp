//
// Created by Michał Markuzel on 10/05/2023.
//

#include "snake_body.h"

coordinates snake_body::get_head_coordinates() {
    return head;
}

snake_body::snake_body(int width, int height) : width(width), height(height) {
    head.x = width / 2;
    head.y = height / 2;

    coordinates q;

    q.x = head.x + 1;
    q.y = head.y;

    body.push_back(q);

    q.x = head.x + 2;
    q.y = head.y;

    body.push_back(q);
}

void snake_body::change_head_coordinates(direction d) {
    switch (d) {
        case UP:
            head.y = head.y - 1;
            break;
        case DOWN:
            head.y = head.y + 1;
            break;
        case LEFT:
            head.x = head.x - 1;
            break;
        case RIGHT:
            head.x = head.x + 1;
            break;
    }
}

void snake_body::make_snake_longer(coordinates q, direction d) {

    if (body.size() > 1)
    {
        body.push_back(body[body.size()-1]);

    for (int i = body.size()-1; i > 0; i--)
        body[i] = body[i-1];

        body[0] = head;
    }

    if (body.size() == 1)
    {
        body.push_back(body[0]);
        body[0] = head;
    }

    if (body.size() == 0)
        body.push_back(head);

    change_head_coordinates(d);
}

coordinates snake_body::get_body_part_coordinates(int body_index) {
    return body[body_index];
}

int snake_body::get_body_length() {
    return body.size();
}

void snake_body::move_whole_body(coordinates q, direction d) {

    if (body.size() == 1)
    {
        body[0] = head;
    }

    if (body.size() > 1)
    {
        for (int i = body.size()-1; i > 0; i--)
            body[i] = body[i-1];

        body[0] = head;
    }

    change_head_coordinates(d);
}

