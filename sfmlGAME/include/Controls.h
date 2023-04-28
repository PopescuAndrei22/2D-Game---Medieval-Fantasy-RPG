#ifndef CONTROLS_H
#define CONTROLS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

class Controls
{
public:
    /* getters */
    sf::Keyboard::Key getMoveLeft() const;
    sf::Keyboard::Key getMoveRight() const;
    sf::Keyboard::Key getMoveUp() const;
    sf::Keyboard::Key getMoveDown() const;
    sf::Keyboard::Key getAttack() const;
    sf::Keyboard::Key getSpellCast() const;
    sf::Keyboard::Key getDash() const;

    /* setters */
    void setMoveLeft(sf::Keyboard::Key);
    void setMoveRight(sf::Keyboard::Key);
    void setMoveUp(sf::Keyboard::Key);
    void setMoveDown(sf::Keyboard::Key);
    void setAttack(sf::Keyboard::Key);
    void setSpellCast(sf::Keyboard::Key);
    void setDash(sf::Keyboard::Key);

    /* class methods */
    sf::Keyboard::Key checkIfKeyIsPressed();

    /* constructors */
    Controls();

    /* destructors */
    ~Controls();

private:
    sf::Keyboard::Key moveUp,moveDown,moveLeft,moveRight; // controls for moving the character
    sf::Keyboard::Key attack; // control for basic attack
    sf::Keyboard::Key spellCast; // control for spell cast
    sf::Keyboard::Key dash;
};

#endif // CONTROLS_H
