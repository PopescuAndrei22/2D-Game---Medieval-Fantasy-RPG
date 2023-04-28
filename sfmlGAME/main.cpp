#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include "GameManagement.h"
#include <typeinfo>
#include "Animation.h"
#include "AnimationState.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080), "2D RPG");
    window.setFramerateLimit(144);

    GameManagement gameManagement(window);

    sf::Clock clock;

    while (window.isOpen())
        {
            float timer = clock.restart().asSeconds();

            bool mouseClick = false;

            sf::Event event;
            while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed || gameManagement.getGameExit()) // possible bug here
                        window.close();

                    if (event.type == sf::Event::MouseWheelMoved)
                        {
                            gameManagement.manageZoom(event.mouseWheel.delta);
                        }
                    if (event.type == sf::Event::MouseButtonPressed)
                        {
                            if (event.mouseButton.button == sf::Mouse::Left)
                                {
                                    mouseClick = true;
                                }
                        }

                }

            gameManagement.setMouseClicked(mouseClick);

            gameManagement.windowManagement(timer);

            gameManagement.draw();

        }

    return 0;
}
