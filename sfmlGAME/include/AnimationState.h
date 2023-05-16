#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

class AnimationState: public sf::Drawable, public sf::Transformable
{
public:

    /* getters */
    std::string getState() const;
    bool getIsFinished();
    bool getIsLooped();
    sf::Vector2f getSize() const;
    const sf::Vertex* getVertices() const;

    /* setters */
    void setState(std::string);
    void setTexture(std::string);
    void setIsLooped(bool);

    void setColor(sf::Color);

    /* class methods */
    void addAnimation(std::string, Animation);
    void update(float);
    void setFrame();
    void stop();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /* constructors */
    AnimationState();

    /* destructors */
    ~AnimationState();

private:
    std::map<std::string, Animation> animations;
    std::string currentState;

    sf::Texture texture;

    sf::Vertex m_vertices[4];
};

#endif // ANIMATIONSTATE_H
