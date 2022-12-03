#include "Character.h"

//getters
Texture getTexture()
{
    return this->texture;
}

//constructors and destructors
Character::Character(string fileName)
{
    this->texture.loadFromFile(fileName); // loading texture
}

Character::~Character()
{

}
