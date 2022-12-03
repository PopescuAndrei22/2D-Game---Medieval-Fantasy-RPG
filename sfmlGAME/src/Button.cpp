#include "Button.h"

Button::Button(bool state, float x, float y, sf::Color c1, sf::Color c2, sf::Color c3, sf::Font &font, string txt, sf::Color color_text):button_text(font,txt,color_text)
{
    this->button.setSize(sf::Vector2f(x, y));
    this->button.setFillColor(c1);
    this->isPressed = state;
    this->STATE_1 = c1;
    this->STATE_2 = c2;
    this->STATE_3 = c3;

    this->button_text.setCharSize((x+y)/13);
}

Button::~Button()
{
    this->SubButtons.clear();
}

RectangleShape Button::getButton() const
{
    return this->button;
}

Vector2f Button::getSize() const
{
    return this->button.getSize();
}

void Button::setPos(float x, float y)
{
    // Change the position of button
    this->button.setPosition(x,y);

    // Calculate the new position of the text associated to the button
    Vector2f p_button = this->button.getSize();
    FloatRect p_text = this->button_text.getSize();

    int dif_x = (p_button.x-p_text.width)/2;
    int dif_y = (p_button.y-p_text.height)/2;

    // Change the position of the text
    this->button_text.setPos(x+dif_x,y+dif_y - (p_text.height/2));
}

void Button::draw(RenderWindow &window)
{
    window.draw(this->button);
    window.draw(this->button_text.getText());

    // drawing sub-buttons;

    if(this->isPressed==true)
        {

            Vector2f thisPos = this->button.getPosition();
            Vector2f thisSize = this->button.getSize();

            Vector2f subSize;
            if(!SubButtons.empty())
                subSize = SubButtons[0].getSize();
            for(unsigned i=0; i<this->SubButtons.size(); i++)
                {
                    this->SubButtons[i].setPos(thisPos.x,thisPos.y+thisSize.y + i*subSize.y);
                    this->SubButtons[i].draw(window);
                }
        }
}

void Button::checkHover(RenderWindow &window)
{
    Vector2i localPos = Mouse::getPosition(window);

    Vector2f p_size = this->button.getSize();
    Vector2f p_pos = this->button.getPosition();

    if((localPos.x >= p_pos.x && localPos.x <= p_pos.x+p_size.x) && (localPos.y >= p_pos.y && localPos.y <= p_pos.y + p_size.y))
        this->button.setFillColor(this->STATE_2);
    else
        {
            if(this->isPressed==true)
                this->button.setFillColor(this->STATE_3);
            else
                this->button.setFillColor(this->STATE_1);
        }

    for(unsigned i=0; i<this->SubButtons.size(); i++)
        this->SubButtons[i].checkHover(window);
}

void Button::setPressState(bool new_state) // setter
{
    this->isPressed=new_state;
}

Color Button::getNormalColor() const
{
    return this->STATE_1;
}

Color Button::getHoverColor() const
{
    return this->STATE_2;
}

Color Button::getPressColor() const
{
    return this->STATE_3;
}

Vector2f Button::getPos() const
{
    return this->button.getPosition();
}

void Button::setNewColor(sf::Color c)
{
    this->button.setFillColor(c);
}

void Button::addSubButton(string txt)
{
    Vector2f thisSize = this->button.getSize();

    Button newButton = *this;

    newButton.button.setSize(Vector2f(thisSize.x,thisSize.y/1.5));
    newButton.button_text.setText(txt);

    newButton.deleteSubButtons();

    this->SubButtons.push_back(newButton);
}

void Button::deleteSubButtons()
{
    this->SubButtons.clear();
}

string Button::getText()
{
    return this->button_text.getString();
}

bool Button::getPressState() const
{
    return this->isPressed;
}

float Button::getSubButtonsSize()
{
    float sum=0;
    if(!this->SubButtons.empty())
        {
            Vector2f thisSize = SubButtons[0].getSize();
            sum += SubButtons.size() * thisSize.y;
        }
    return sum;
}

bool Button::haveSubButtons() const
{
    if(!this->SubButtons.empty())
        return true;
    return false;
}

bool Button::buttonIsPressed(float x, float y) const
{
    Vector2f p_size = this->button.getSize();
    Vector2f p_pos = this->button.getPosition();

    if((x >= p_pos.x && x <= p_pos.x+p_size.x) && (y >= p_pos.y && y <= p_pos.y + p_size.y))
        return true;
    return false;
}

vector <Button> Button::getSubButtons()
{
    return this->SubButtons;
}

void Button::setStateSubButtons(int pos)
{
    for(unsigned i=0;i<this->SubButtons.size();i++)
    {
        if(i==pos)
            this->SubButtons[i].setPressState(true);
        else
            this->SubButtons[i].setPressState(false);
    }
}
