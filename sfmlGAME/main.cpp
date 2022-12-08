#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Animation.h"
#include "Controls.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(sf::VideoMode(900, 900), "2D RPG");

    Character character;
    Animation animation("sprites/characters/hero1.png",18,33);
    Controls controls;
    Clock clock;

    while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if(event.type == Event::EventType::KeyPressed)
                    {
                        animation.moveCharacter(controls,event.key.code,character.getSpeed());
                    }
                    else
                        animation.setDirection(0); // i will modify this later, after i will improve the design for a better code
                }

            window.clear(Color(Color::Black));

            // must be placed after animation.moveCharacter because of the direction issue (would be 0), but i can change the code for that later
            animation.handleAnimation(clock.restart().asSeconds());

            window.draw(animation.getSprite());

            window.display();
        }

    return 0;
}
