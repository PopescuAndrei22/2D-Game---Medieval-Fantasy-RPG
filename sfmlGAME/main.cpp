#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>
#include "Animation.h"
#include "Input.h"
#include "Character.h"
using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(sf::VideoMode(900, 900), "2D RPG");

    Character hero("sprites/characters/hero1.png");
    Animation animationHero(hero.getTexture(),18,33);
    Input input(hero);

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
                        input.movementInput(event.key.code, hero);
                    }
                }

            window.clear(Color(Color::Black));

            animationHero.handleAnimation(clock.restart().asSeconds());
            window.draw(animationHero.getSprite());

            window.display();
        }

    return 0;
}
