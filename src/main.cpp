// sfml
#include <SFML/Graphics.hpp>
// delay
#include <unistd.h>
#include "snake_board.h"
#include "board_view.h"
#include "snake_logic.h"
#include "snake_body.h"
#include "score.h"

#define WIDTH 30
#define HEIGHT 15

int main() {

    snake_board plansza(WIDTH, HEIGHT);
    snake_body snake(WIDTH, HEIGHT);
    score wyniki("scores.txt");
    snake_logic logika(snake, plansza, wyniki);
    board_view widok(plansza, snake, logika, wyniki);
    sf::RenderWindow window(sf::VideoMode(WIDTH * 25, HEIGHT * 25), "Snake");

    int counter = 0;

    while (window.isOpen()) {

        // delay na 0.01 sek
        usleep(0.1 * 1000);
        counter++;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            else {
                // podejmowanie działań
                logika.handle_event(event, window);
            }
        }

        //delay zależny od poziomu trudności
        if (counter >= 200 * logika.get_game_lvl()) {
            // poruszanie wężem
            logika.gameplay();
            counter = 0;
        }

        window.clear(sf::Color::Black);
        // wyświetlanie planszy
        widok.draw(window);
        window.display();
    }

    return 0;
}
