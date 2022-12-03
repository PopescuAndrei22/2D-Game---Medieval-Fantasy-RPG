#include "Textbox.h"

Textbox::Textbox(float x, float y, float xpos, float ypos, Font& font, string txt, bool onMiddle, string empty_text, float text_size, bool put_inside_text)
{
    this->empty_text = empty_text;

    this->box.setPosition(Vector2f(xpos,ypos));
    this->box.setSize(Vector2f(x,y));
    this->box.setFillColor(Color::White);

    this->txt.setFont(font);
    this->txt.setString(txt);
    this->txt.setFillColor(Color::White);
    this->txt.setCharacterSize(y);
    if(onMiddle==false)
        this->txt.setPosition(Vector2f(xpos,ypos-y-y/2));
    else
    {
        FloatRect getLimits = this->txt.getGlobalBounds();
        this->txt.setPosition(Vector2f((x-getLimits.width)/2+xpos,ypos-y-y/2));
    }

    this->is_selected = false;
    this->addInBox = "";

    if(put_inside_text==true)
        this->text_in_box.setCharacterSize(text_size);
    else
        this->text_in_box.setCharacterSize(y);
    this->text_in_box.setFont(font);
    this->text_in_box.setString("A");
    this->text_in_box.setFillColor(Color::Black);

    //setting the text in the middle ( on y axis in the text box )
    FloatRect setMiddle = this->text_in_box.getGlobalBounds();
    float dif = (y - setMiddle.height) / 2;
    this->text_in_box.setPosition(Vector2f(xpos,ypos));
}

void Textbox::draw(RenderWindow &window)
{
    string t = "";
    if(this->is_selected==true)
        t = "l";

    if(this->is_selected==false && this->addInBox=="")
        this->text_in_box.setString(this->empty_text);
   else
        this->text_in_box.setString(this->addInBox + t);

    window.draw(this->box);
    window.draw(this->txt);
    window.draw(this->text_in_box);
}

Vector2f Textbox::getSize() const
{
    return this->box.getSize();
}

Vector2f Textbox::getPos() const
{
    return this->box.getPosition();
}

bool Textbox::MouseClickEvent(float x, float y) const
{
    Vector2f p_size = this->box.getSize();
    Vector2f p_pos = this->box.getPosition();

    if((x >= p_pos.x && x <= p_pos.x+p_size.x) && (y >= p_pos.y && y <= p_pos.y + p_size.y))
        return true;
    return false;
}

bool Textbox::getSelectState() const
{
    return this->is_selected;
}

void Textbox::setSelectState(bool new_state)
{
    this->is_selected = new_state;
}

void Textbox::addCharacter(int code)
{
    if(code==BACKSPACE_CODE)
        {
            if(this->addInBox.size()>0)
                this->addInBox.pop_back();
        }
    else
        this->addInBox += (char)code;
}

void Textbox::resetText()
{
    this->addInBox = "";
}

string Textbox::getText() const
{
    return this->addInBox;
}
