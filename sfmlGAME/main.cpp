#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Controls.h"
#include "Animation.h"
#include "AnimationCharacter.h"
#include "Camera.h"
#include "CharacterMove.h"
#include "Map.h"

using namespace sf;
using namespace std;

// timer universally
// to make this->setFrame universally, just modifying this->currentFrame in functions
// be careful at currentFrame values
// IMPORTANT: must delete collision array after using update function in character move

int main()
{
    RenderWindow window(sf::VideoMode(900, 900), "2D RPG");

    Character hero;
    Controls controls;
    Clock clock;
    Camera camera;
    // sa am grija la extensii gen .png sau .jpg -> voi modifica in constructor
    AnimationCharacter heroAnimation("hero");
    CharacterMove characterMove;
    Map map("map1","level1");
    characterMove.updateLevelDetails(map);
    hero.setCharacterSize(heroAnimation.getFrameSize());
    camera.setMapSize(map.getMapSize());

    while (window.isOpen())
        {
            float timer = clock.restart().asSeconds();

            sf::Event event;
            while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    if (event.type == sf::Event::MouseWheelMoved)
                        {
                            camera.zoomEvent(event.mouseWheel.delta);
                        }
                }

            heroAnimation.handleAnimation(hero,controls,timer);
            characterMove.handleMovement(controls,&hero,timer);
            camera.handleView(hero);

            window.clear(Color(Color::Black));

            window.setView(camera.getView());
            window.draw(map.getMap());
            window.draw(heroAnimation.getSprite());

            window.display();
        }

    return 0;
}
