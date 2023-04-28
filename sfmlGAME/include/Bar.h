#ifndef BAR_H
#define BAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

class Bar
{
    public:

        /* class methods */
        void setPosition(sf::Vector2f);
        void setPositionEnemy(sf::Vector2f,sf::Vector2f);

        void updateBar(int);

        void setBar(std::string, int);

        void draw(sf::RenderWindow&);
        /* constructors */
        Bar();

        /* destructors */
        ~Bar();

    private:

        sf::Texture textureBar;
        sf::Texture textureEmptyBar;

        sf::Sprite iconSprite;
        sf::Sprite barSprite;

        std::vector<sf::Sprite> bars;

        int barValue;
};

#endif // BAR_H
