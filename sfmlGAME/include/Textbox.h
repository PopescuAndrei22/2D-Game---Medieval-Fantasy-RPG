#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define BACKSPACE_CODE 8

class Textbox
{
private:
    RectangleShape box;
    Text txt,text_in_box;
    bool is_selected;
    int limit;
    string empty_text;
    string addInBox;

public:
    Textbox(float,float,float,float,Font&,string,bool=false,string="",float=0,bool=false);

    void draw(RenderWindow&);

    Vector2f getSize() const;
    Vector2f getPos() const;

    bool MouseClickEvent(float, float) const;

    bool getSelectState() const;

    void setSelectState(bool);

    void addCharacter(int);

    void resetText();

    string getText() const;
};

#endif // TEXTBOX_H
