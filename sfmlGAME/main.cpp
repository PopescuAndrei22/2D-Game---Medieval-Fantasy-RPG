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
#include "GameManagement.h"
#include <typeinfo>

using namespace sf;
using namespace std;

// .png and .jpg extensions

int main()
{

    string pathValues = "values/options/options.json";
    ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);
    float x = (data["windowSizeX"].is_null()?0:(float)data["windowSizeX"]);
    float y = (data["windowSizeY"].is_null()?0:(float)data["windowSizeY"]);

    RenderWindow window(sf::VideoMode(x, y), "2D RPG");
    // can be changed from settings
    window.setFramerateLimit(144);

    GameManagement gameManagement;
    gameManagement.setCharacters();

    Clock clock;

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
                            gameManagement.manageZoom(event.mouseWheel.delta);
                        }
                }

            gameManagement.manageInsideWindow(timer);

            window.clear(Color(Color::Black));

            gameManagement.draw(&window);

            window.display();
        }

    return 0;
}
