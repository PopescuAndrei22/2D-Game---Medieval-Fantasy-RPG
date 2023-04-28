#include "Menu.h"

/* getters */
bool Menu::getIsButtonPressed() const
{
    return this->isButtonPressed;
}

std::string Menu::getButtonPressedName() const
{
    return this->buttonPressedName;
}

/* setters */
void Menu::setWindowSize(sf::Vector2f windowSize)
{
    this->windowSize = windowSize;
}

void Menu::setIsButtonClicked(bool isButtonClicked)
{
    this->isButtonClicked = isButtonClicked;
}

void Menu::draw(sf::RenderWindow &renderWindow)
{
    // drawing menu
    renderWindow.draw(this->backgroundSprite);

    renderWindow.draw(this->gameName);

    for(unsigned i=0; i<this->buttons.size(); i++)
        {
            if(this->buttons[i]->getIsVisible())
                {
                    this->buttons[i]->draw(renderWindow);
                }
        }
}

void Menu::manageMenu(sf::RenderWindow &renderWindow)
{
    // reseting view
    sf::View defaultView(sf::FloatRect(0.f,0.f,this->windowSize.x,this->windowSize.y));
    renderWindow.setView(defaultView);

    this->isButtonPressed = false;

    sf::Vector2i mousePosition = sf::Mouse::getPosition(renderWindow);

    for(unsigned i=0; i<this->buttons.size(); i++)
        {
            if(!this->buttons[i]->getIsVisible())
                continue;

            this->buttons[i]->hoverButton(mousePosition);

            if(this->buttons[i]->isButtonClicked(mousePosition,this->isButtonClicked))
                {
                    this->isButtonPressed = true;

                    std::string buttonName = this->buttons[i]->getButtonName();

                    this->buttonPressedName = this->buttons[i]->getButtonName();
                }
        }
}

void Menu::setButtonsVisibility(std::string menuType)
{
    for(unsigned i=0; i<this->buttons.size(); i++)
        {
            this->buttons[i]->setIsVisible(false);
        }

    if(menuType == "default") // main menu
        {
            for(unsigned i=0; i<this->buttons.size(); i++)
                {
                    std::string buttonName = this->buttons[i]->getButtonName();

                    if(buttonName == "Start" || buttonName == "Exit")
                        this->buttons[i]->setIsVisible(true);
                }
        }
    else // resume while in-game
        {
            for(unsigned i=0; i<this->buttons.size(); i++)
                {
                    std::string buttonName = this->buttons[i]->getButtonName();

                    if(buttonName == "Resume" || buttonName == "Main Menu"  || buttonName == "Exit")
                        this->buttons[i]->setIsVisible(true);
                }
        }
}

void Menu::LayoutManager()
{
    // positioning the game title
    sf::FloatRect getTitleData = this->gameName.getGlobalBounds();

    float blankSpaceWidth = this->windowSize.x - getTitleData.width;
    blankSpaceWidth /= 2.0f;

    this->gameName.setPosition(sf::Vector2f(blankSpaceWidth,this->windowSize.y / 30.0f));

    // positioning the buttons

    float distanceBetweenButtons = this->windowSize.y / 30.0f;

    sf::Vector2f lastPlacedComponent;
    lastPlacedComponent = this->gameName.getPosition();
    lastPlacedComponent.y += this->gameName.getGlobalBounds().height * 3;

    for(unsigned i=0; i<this->buttons.size(); i++)
        {
            if(!this->buttons[i]->getIsVisible())
                continue;

            // placing the button on center in width
            float distanceButtonWidth = this->windowSize.x - this->buttons[i]->getButtonWidth();
            distanceButtonWidth /= 2.0f;
            lastPlacedComponent.x = distanceButtonWidth;

            this->buttons[i]->setButtonPosition(lastPlacedComponent);

            lastPlacedComponent = this->buttons[i]->getButtonPosition();
            lastPlacedComponent.y += this->buttons[i]->getButtonHeight() + distanceBetweenButtons;
        }
}

Menu::Menu()
{
    std::string pathValues = "values/options/options.json";
    std::ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    try
        {
            this->windowSize.x = (data["windowSizeX"].is_null()?0:(float)data["windowSizeX"]);
            this->windowSize.y = (data["windowSizeY"].is_null()?0:(float)data["windowSizeY"]);
        }
    catch(const nlohmann::json::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    file.close();

    Button *buttonResume = new Button();
    buttonResume->setValues(this->windowSize,"Resume");
    buttonResume->setIsVisible(false);

    Button *buttonStart = new Button();
    buttonStart->setValues(this->windowSize,"Start");

    Button *buttonReturn = new Button();
    buttonReturn->setValues(this->windowSize,"Main Menu");
    buttonReturn->setIsVisible(false);

    Button *buttonExit = new Button();
    buttonExit->setValues(this->windowSize,"Exit");

    this->buttons.push_back(buttonResume);
    this->buttons.push_back(buttonStart);
    this->buttons.push_back(buttonReturn);
    this->buttons.push_back(buttonExit);

    // game name
    this->font.loadFromFile("fonts/ARCADECLASSIC.ttf");
    this->gameName.setFont(this->font);
    this->gameName.setColor(sf::Color(255, 220, 182));
    this->gameName.setString("2D Game");
    this->gameName.setCharacterSize(this->windowSize.y / 13.f);

    this->LayoutManager();

    this->buttonPressedName = "";
    this->isButtonPressed = false;

    this->isButtonClicked = false;

    // loading background image

    std::string filePathBackground = "sprites/background/background2.png";

    this->backgroundTexture.loadFromFile(filePathBackground);

    this->backgroundSprite.setTexture(this->backgroundTexture);
}

Menu::~Menu()
{

}
