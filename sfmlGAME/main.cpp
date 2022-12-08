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
            float timer = clock.restart().asSeconds();

            sf::Event event;
            while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if(event.type == Event::EventType::KeyPressed)
                    {
                        // to do
                    }
                }

            animation.moveCharacter(controls,controls.checkIfKeyIsPressed(),character.getSpeed(),timer);

            window.clear(Color(Color::Black));

            animation.handleAnimation(timer);

            window.draw(animation.getSprite());

            window.display();
        }

    return 0;
}
