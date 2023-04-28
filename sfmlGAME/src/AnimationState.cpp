#include "AnimationState.h"

/* getters */
std::string AnimationState::getState() const
{
    return this->currentState;
}

bool AnimationState::getIsFinished()
{
    return this->animations[this->currentState].getIsFinished();
}

/* setters */
void AnimationState::setState(std::string state)
{
    if(this->currentState != state && this->animations.count(this->currentState) != 0)
        {
            this->animations[this->currentState].stop();
        }

    this->currentState = state;

    if(this->animations.count(this->currentState) != 0)
        {
            this->animations[this->currentState].play();
        }
}

void AnimationState::setTexture(std::string filePath)
{
    this->texture.loadFromFile(filePath);
}

void AnimationState::setIsLooped(bool isLooped)
{
    this->animations[this->currentState].setIsLooped(isLooped);
}

void AnimationState::setColor(sf::Color color)
{
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}

/* class methods */
void AnimationState::addAnimation(std::string state, Animation animation)
{
    this->animations[state] = animation;
}

void AnimationState::update(float timer)
{
    if(this->animations.count(this->currentState) == 0)
        return;

    this->animations[this->currentState].update(timer);

    this->setFrame();
}

void AnimationState::setFrame()
{
    if(this->animations.count(this->currentState) == 0)
        return;

    sf::IntRect rect = this->animations[this->currentState].getFrame();

    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
    m_vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
    m_vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

    float left = static_cast<float>(rect.left) + 0.0001f;
    float right = left + static_cast<float>(rect.width);
    float top = static_cast<float>(rect.top);
    float bottom = top + static_cast<float>(rect.height);

    m_vertices[0].texCoords = sf::Vector2f(left, top);
    m_vertices[1].texCoords = sf::Vector2f(left, bottom);
    m_vertices[2].texCoords = sf::Vector2f(right, bottom);
    m_vertices[3].texCoords = sf::Vector2f(right, top);
}

void AnimationState::stop()
{
    this->animations[this->currentState].stop();
}

void AnimationState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &this->texture;
    target.draw(m_vertices, 4, sf::Quads, states);
}

/* constructors */
AnimationState::AnimationState()
{
    this->currentState = "";
}

/* destructors */
AnimationState::~AnimationState()
{

}
