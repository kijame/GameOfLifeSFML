#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "GameBoard.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Conways Game of Life");

    GameBoard board;

    bool sim_running = false;

    while (window.isOpen())
    {
        // event loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed)
            {
                auto pos = sf::Mouse::getPosition(window);
                int x = pos.y;
                int y = pos.x;
                board.click(x, y);
            }

            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    sim_running = !sim_running;
                    //Test
                    //sim_running = true;
                }
                else if (event.key.code == sf::Keyboard::BackSpace) {
                    board.reset();
                    sim_running = false;
                }
            }
            //else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            //{
            //    sim_running = true;
            //  //board.iterate();
            //}

            //else if (event.type == sf::Event::KeyPressed)
            //{
            //  if (event.key.code == sf::Keyboard::BackSpace)
            //  {
            //    board.reset();
            //    sim_running = false;
            //  }
            //} //Hello
        }
        if (sim_running) {
            board.iterate();
        }

        window.clear();

        board.draw(&window);

        window.display();
    }

    return 0;
}
