#include "Button.h"

/* getters */
bool Button::getIsVisible() const
{
    return this->isVisible;
}

sf::Vector2f Button::getButtonPosition()
{
    return this->button.getPosition();
}

float Button::getButtonWidth()
{
    return this->button.getGlobalBounds().width;
}

float Button::getButtonHeight()
{
    return this->button.getGlobalBounds().height;
}

std::string Button::getButtonName()
{
    return this->buttonName;
}

/* setters */
void Button::setIsVisible(bool isVisible)
{
    this->isVisible = isVisible;
}

void Button::setButtonPosition(sf::Vector2f buttonPosition)
{
    this->button.setPosition(buttonPosition);

    this->buttonText.setPosition(buttonPosition);

    // placing the button text in the center

    sf::FloatRect buttonDetails = this->button.getGlobalBounds();
    sf::FloatRect buttonTextDetails = this->buttonText.getGlobalBounds();

    sf::Vector2f newTextPosition;
    newTextPosition.x = buttonTextDetails.left;
    newTextPosition.y = buttonTextDetails.top;

    float blankSpaceWidth = buttonDetails.width - buttonTextDetails.width;
    blankSpaceWidth /= 2.0f;
    newTextPosition.x += blankSpaceWidth;

    float blankSpaceHeight = buttonDetails.height - buttonTextDetails.height;
    blankSpaceHeight /= 2.0f;
    newTextPosition.y += blankSpaceHeight;

    newTextPosition.y -= buttonTextDetails.height / 2.0f;

    this->buttonText.setPosition(newTextPosition);
}

/* class methods */

bool Button::isMouseCursorOnButton(sf::Vector2i mousePosition)
{
    sf::FloatRect buttonDetails = this->button.getGlobalBounds();

    if(mousePosition.x >= buttonDetails.left && mousePosition.x <= buttonDetails.left + buttonDetails.width)
        {
            if(mousePosition.y >= buttonDetails.top && mousePosition.y <= buttonDetails.top + buttonDetails.height)
                {
                    return true;
                }
        }

    return false;
}

void Button::hoverButton(sf::Vector2i mousePosition)
{
    if(this->isMouseCursorOnButton(mousePosition))
        this->button.setFillColor(this->hoverButtonColor);
    else
        this->button.setFillColor(this->defaultButtonColor);
}

bool Button::isButtonClicked(sf::Vector2i mousePosition, bool isClicked)
{
    if(this->isMouseCursorOnButton(mousePosition))
        {
            if(isClicked)
                {
                    return true;
                }
        }

    return false;
}

void Button::setValues(sf::Vector2f windowSize, std::string buttonName)
{
    sf::Vector2f buttonPosition = sf::Vector2f(0,0); // default button position
    // button

    this->buttonName = buttonName;

    this->button.setSize(sf::Vector2f(windowSize.x / 5.0f, windowSize.y / 13.0f));

    this->button.setFillColor(this->defaultButtonColor);

    // button text

    this->font.loadFromFile("fonts/joystix.otf");

    this->buttonText.setFont(this->font);

    this->buttonText.setFillColor(sf::Color(8, 131, 149));

    this->buttonText.setCharacterSize(windowSize.y / 35.0f);

    this->buttonText.setString(buttonName);

    // setting button position

    this->setButtonPosition(buttonPosition);

}

void Button::draw(sf::RenderWindow &renderWindow)
{
    if(this->getIsVisible() == false)
        return;

    renderWindow.draw(this->button);

    renderWindow.draw(this->buttonText);
}

Button::Button()
{
    this->setIsVisible(true);

    this->defaultButtonColor = sf::Color(sf::Color(238, 238, 238, 120));

    this->hoverButtonColor = sf::Color::Cyan;
}

Button::~Button()
{

}
