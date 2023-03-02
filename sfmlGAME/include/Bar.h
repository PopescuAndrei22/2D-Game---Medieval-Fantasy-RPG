#ifndef BAR_H
#define BAR_H
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// class for bars such as health, mana etc
class Bar
{
    public:
        // setters
        void setPosition(Vector2f);

        // draw on window
        void draw(RenderWindow*);

        // managing bar, meaning for example in health bar to adjust the bars (based on current life)
        void manageBar(int);

        // setting the bar for enemies
        void setPositionEnemy(Vector2f, Vector2f);

        Bar(string,string,int);
        ~Bar();

    private:
        Texture textureBar,textureEmptyBar;

        Sprite icon,a;

        vector <Sprite> bars;

        int barBlock; // how many units a bar has, for example 1 bar = 25 points of life or mana
};

#endif // BAR_H
