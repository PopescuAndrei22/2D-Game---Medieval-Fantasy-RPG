#include "Panel.h"

Panel::Panel(int x, int y, sf::Color c)
{
    this->rectangle.setSize(sf::Vector2f(x, y));
    this->rectangle.setFillColor(c);
}

Panel::~Panel()
{
    PanelButtons.clear();
}

RectangleShape Panel::getRectangle() const
{
    return this->rectangle;
}

void Panel::addButton(Button b)
{
    this->PanelButtons.push_back(b);
}

void Panel::printButtons(RenderWindow &window)
{
    Vector2f length_panel = this->rectangle.getSize();
    Vector2f pos_panel = this->rectangle.getPosition();

    float sum=0;

    for(unsigned i=0; i<this->PanelButtons.size(); i++)
        {
            Vector2f length_button = this->PanelButtons[i].getSize();

            int dif = (length_panel.x - length_button.x)/2;

            this->PanelButtons[i].setPos(dif,(((float)i+1)*length_panel.y/20)+(float)i*length_button.y+sum+pos_panel.y);

            if(this->PanelButtons[i].getPressState() == true)
                sum += PanelButtons[i].getSubButtonsSize();

            this->PanelButtons[i].draw(window);

        }
}

void Panel::HoverButtons(RenderWindow &window)
{
    for(unsigned i=0; i<PanelButtons.size(); i++)
        this->PanelButtons[i].checkHover(window);
}

void Panel::ButtonPressedEvent(int x, int y)
{
    unsigned pos = PanelButtons.size()+1, posSubButton = -1;

    bool subButton = false, foundButton = false;

    for(unsigned i=0; i<this->PanelButtons.size(); i++)
        {
            if(this->PanelButtons[i].haveSubButtons()==true)
                {
                    if(this->PanelButtons[i].buttonIsPressed(x,y)==true)
                        {
                            if(this->PanelButtons[i].getPressState()==false)
                                this->PanelButtons[i].setPressState(true);
                            else
                                this->PanelButtons[i].setPressState(false);
                        }

                    vector <Button> CheckPressed = this->PanelButtons[i].getSubButtons();

                    if(this->PanelButtons[i].getPressState()==true)
                        {
                            for(unsigned j=0; j<CheckPressed.size(); j++)
                                {
                                    if(CheckPressed[j].buttonIsPressed(x,y)==true)
                                        {
                                            foundButton = subButton = true;
                                            pos = i;
                                            posSubButton = j;
                                            break;
                                        }
                                }
                        }
                }
            else
                {
                    if(this->PanelButtons[i].buttonIsPressed(x,y)==true)
                        {
                            pos=i;
                            foundButton = true;
                        }
                }

            if(foundButton==true)
                break;
        }

    if(pos == PanelButtons.size()+1)
        return;

    for(unsigned i=0; i<this->PanelButtons.size(); i++)
        {
            if(this->PanelButtons[i].haveSubButtons()==true)
                {
                    if(i==pos)
                        this->PanelButtons[i].setStateSubButtons(posSubButton);
                    else
                        this->PanelButtons[i].setStateSubButtons(-1);
                }
            else
                {
                    if(i!=pos)
                        this->PanelButtons[i].setPressState(false);
                    else
                        this->PanelButtons[i].setPressState(true);
                }
        }
}

void Panel::createSubButton(string txt, string new_txt)
{
    for(unsigned i=0; i<PanelButtons.size(); i++)
        {
            if(PanelButtons[i].getText()==txt)
                {
                    PanelButtons[i].addSubButton(new_txt);
                    return;
                }
        }
}

bool Panel::ButtonIsSelected(string txt)
{
    for(unsigned i=0; i<this->PanelButtons.size(); i++)
        {
            if(this->PanelButtons[i].haveSubButtons()==false)
                {
                    if(this->PanelButtons[i].getText()==txt && this->PanelButtons[i].getPressState()==true)
                        return true;
                }
            else
                {
                    vector <Button> CheckPressed = this->PanelButtons[i].getSubButtons();
                    for(unsigned j=0; j<CheckPressed.size(); j++)
                        {
                            if(CheckPressed[j].getText()==txt && CheckPressed[j].getPressState()==true)
                                return true;
                        }
                }
        }
    return false;
}

Vector2f Panel::getPanelSize() const
{
    return this->rectangle.getSize();
}

bool Panel::doesTheButtonExist(string txt)
{
    for(unsigned i=0; i<this->PanelButtons.size(); i++)
        {
            if(this->PanelButtons[i].haveSubButtons()==false)
                {
                    if(this->PanelButtons[i].getText()==txt)
                        return true;
                }
            else
                {
                    vector <Button> CheckPressed = this->PanelButtons[i].getSubButtons();
                    for(unsigned j=0; j<CheckPressed.size(); j++)
                        {
                            if(CheckPressed[j].getText()==txt)
                                return true;
                        }
                }
        }
    return false;
}

void Panel::setPos(float x, float y)
{
    this->rectangle.setPosition(Vector2f(x,y));
}
