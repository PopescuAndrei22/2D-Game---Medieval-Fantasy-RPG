#ifndef TEXTBOXPAGEHANDLER_H
#define TEXTBOXPAGEHANDLER_H
#include "Textbox.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Button.h"
#include <sstream>
#include <windows.h>
#include <mysql.h>
#include <cstring>

using namespace std;
using namespace sf;

class TextBoxPageHandler
{
private:
    vector <Textbox> Form;
    vector <Button> Form_Buttons;
    Text Headline;
    string Button_Name;
    RectangleShape border;

public:
    void addTextBox(Textbox);

    void addButton(Button);

    ~TextBoxPageHandler();
    TextBoxPageHandler(string);

    void draw(RenderWindow&);

    void CheckSelection(float, float);

    void FillText(int);

    void changePosButtons(int, float, float);

    void HoverButtons(RenderWindow&);

    void setHeadline(Font&, int, Color, string);

    void setPosHeadline(float, float);

    FloatRect getSize() const;

    Text getHeadline() const;

    string getButtonName() const;

    void ButtonPressedEvent(int, int, MYSQL*);

    void ResetText();

    void SQL_Update(string, MYSQL*);
};

#endif // TEXTBOXPAGEHANDLER_H
