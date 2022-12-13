#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Controls.h"
#include "Animation.h"
#include "AnimationCharacter.h"

using namespace sf;
using namespace std;

// timer universally
// to make this->setFrame universally, just modifying this->currentFrame in functions
// be careful at currentFrame values

int main()
{
    // ("sprites/characters/hero1.png",18,33) will be in the main animation class

    RenderWindow window(sf::VideoMode(900, 900), "2D RPG");

    Character hero;
    Controls controls;
    Clock clock;

    // sa am grija la extensii gen .png sau .jpg
    AnimationCharacter heroAnimation("hero",18,33);
    heroAnimation.setWindowSize(window.getSize());

    while (window.isOpen())
        {
            float timer = clock.restart().asSeconds();

            sf::Event event;
            while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

            heroAnimation.handleAnimation(controls,controls.checkIfKeyIsPressed(),timer);

            window.clear(Color(Color::Black));

            window.draw(heroAnimation.getSprite());

            window.display();
        }

    return 0;
}
