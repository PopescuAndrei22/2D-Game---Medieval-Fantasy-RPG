#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Controls.h"
#include "Animation.h"
#include "AnimationCharacter.h"
#include "Camera.h"
#include "CharacterMove.h"
#include "Map.h"
#include "Enemy.h"
#include "Bar.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(sf::VideoMode(900, 900), "2D RPG");
    window.setFramerateLimit(144);

    Character hero("hero");
    Enemy enemy("skeleton");

    Controls controls;
    Clock clock;
    Camera camera;

    // to be careful to png and jpg extensions
    AnimationCharacter heroAnimation("hero");
    AnimationCharacter enemyAnimation("skeleton");
    //get these values from json file
    hero.setCharacterSize(heroAnimation.getFrameSize());
    enemy.setCharacterSize(enemyAnimation.getFrameSize());

    CharacterMove characterMove;
    Map map("map1","level3");

    camera.setMapSize(map.getMapSize());

    enemy.getGraph(&map);

    // health bar
    Bar health("health_bar","empty_bar",hero.getHealth());
    //Bar mana("magic_bar","empty_bar");

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

            enemy.getPlayerState(&hero);

            controls.handleControls(&hero);
            enemy.AI(timer);

            characterMove.handleMovement(&hero,timer,&map);
            characterMove.handleMovement(&enemy,timer,&map);

            heroAnimation.handleAnimation(&hero,timer);
            enemyAnimation.handleAnimation(&enemy,timer);

            // placing the health bar in the top left corner
            health.setPosition(camera.getTopLeftCorner());
            health.manageBar(hero.getCurrentHealth());

            window.clear(Color(Color::Black));

            camera.handleView(hero);
            window.setView(camera.getView());

            window.draw(map.getMap());

            window.draw(heroAnimation.getSprite());
            window.draw(enemyAnimation.getSprite());

            health.draw(&window);

            window.display();
        }

    return 0;
}
