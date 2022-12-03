#include "TextBoxPageHandler.h"

TextBoxPageHandler::TextBoxPageHandler(string txt)
{
    this->Button_Name = txt;
}

TextBoxPageHandler::~TextBoxPageHandler()
{
    this->Form.clear();
}

void TextBoxPageHandler::addTextBox(Textbox ob)
{
    this->Form.push_back(ob);
}

void TextBoxPageHandler::draw(RenderWindow &window)
{
    for(unsigned i=0; i<this->Form.size(); i++)
        this->Form[i].draw(window);

    for(unsigned i=0; i<this->Form_Buttons.size(); i++)
        this->Form_Buttons[i].draw(window);
}

void TextBoxPageHandler::CheckSelection(float x, float y)
{
    unsigned pos = Form.size()+1;

    for(unsigned i=0; i<this->Form.size(); i++)
    {
        if(this->Form[i].MouseClickEvent(x,y)==true)
        {
            pos = i;
            break;
        }
    }

    for(unsigned i=0; i<this->Form.size(); i++)
    {
        if(i==pos)
            this->Form[i].setSelectState(true);
        else
            this->Form[i].setSelectState(false);
    }
}

void TextBoxPageHandler::FillText(int code)
{
    for(unsigned i=0; i<this->Form.size(); i++)
    {
        if(this->Form[i].getSelectState()==true)
        {
            this->Form[i].addCharacter(code);
            return;
        }
    }
}

void TextBoxPageHandler::addButton(Button ob)
{
    this->Form_Buttons.push_back(ob);
}

void TextBoxPageHandler::changePosButtons(int limit_right, float distance, float height)
{
    float sum=0;

    for(unsigned i=0; i<this->Form_Buttons.size(); i++)
    {
        Vector2f button_details = this->Form_Buttons[i].getSize();

        this->Form_Buttons[i].setPos(limit_right-distance*(i+1)-button_details.x-sum,height);

        sum += button_details.x;
    }
}

void TextBoxPageHandler::HoverButtons(RenderWindow &window)
{
    for(unsigned i=0; i<this->Form_Buttons.size(); i++)
        this->Form_Buttons[i].checkHover(window);
}

void TextBoxPageHandler::setHeadline(Font &font, int charSize, Color c, string txt)
{
    this->Headline.setFont(font);
    this->Headline.setCharacterSize(charSize);
    this->Headline.setFillColor(c);
    this->Headline.setString(txt);
}

void TextBoxPageHandler::setPosHeadline(float xpos, float ypos)
{
    this->Headline.setPosition(Vector2f(xpos,ypos));
}

FloatRect TextBoxPageHandler::getSize() const
{
    return this->Headline.getGlobalBounds();
}

Text TextBoxPageHandler::getHeadline() const
{
    return this->Headline;
}

string TextBoxPageHandler::getButtonName() const
{
    return this->Button_Name;
}

void TextBoxPageHandler::ResetText()
{
    for(unsigned index=0; index<this->Form.size(); index++)
    {
        this->Form[index].resetText();
    }
}

void TextBoxPageHandler::SQL_Update(string txt, MYSQL* conn)
{
    string form_text[10];

    unsigned n = this->Form.size();

    for(unsigned index=0; index<n; index++)
        form_text[index] = this->Form[index].getText();

    int qstate = 0;
    stringstream ss;

    if(txt == "Add student")
        ss << "INSERT INTO studenti(prenume, nume, adresa, oras, email, telefon) VALUES('"<< form_text[0] << "','" << form_text[1] << "','" << form_text[2] << "','" << form_text[3] << "','" << form_text[4] << "','" << form_text[5] << "')";
    else if(txt == "Delete student")
    {
        int ID = -1 ;
        string id_text = form_text[0];

        long long new_id = 0;
        for(unsigned i=0; i<id_text.size(); i++)
            new_id = new_id*10 + (int)id_text[i] - '0';

        if(id_text.size()>0)
            ID = new_id;

        if(ID!=-1)
            ss << "DELETE FROM studenti WHERE ID = '" << ID << "'";
    }
    else if(txt == "Add book")
        ss << "INSERT INTO carti(autor, editor, carte, categorie, cantitate) VALUES('"<< form_text[0] << "','" << form_text[1] << "','" << form_text[2] << "','" << form_text[3] << "','" << form_text[4] << "')";
    else if(txt == "Delete book")
    {
        int ID = -1 ;
        string id_text = form_text[0];

        long long new_id = 0;
        for(unsigned i=0; i<id_text.size(); i++)
            new_id = new_id*10 + (int)id_text[i] - '0';

        if(id_text.size()>0)
            ID = new_id;

        if(ID!=-1)
            ss << "DELETE FROM carti WHERE ID = '" << ID << "'";
    }
    else if(txt == "Edit book")
    {

    }

    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    if(qstate==0)
        cout<<"Record was succesful!"<<'\n';
    else
        cout<<"Record failed!"<<'\n';
}

void TextBoxPageHandler::ButtonPressedEvent(int x, int y, MYSQL* conn)
{
    for(unsigned index=0; index<this->Form_Buttons.size(); index++)
    {
        if(this->Form_Buttons[index].buttonIsPressed(x,y))
        {
            if(index==0)
                this->SQL_Update(this->Form_Buttons[index].getText(),conn);
            this->ResetText();
        }
    }
}
