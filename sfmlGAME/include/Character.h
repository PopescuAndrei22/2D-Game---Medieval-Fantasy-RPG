#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Character
{
    public:
        //getters
        Texture getTexture();

        Character(string);
        ~Character();

    private:
        Texture texture;

        int speed; // measured in x%
};

#endif // CHARACTER_H
