#include "Camera.h"

// getters
sf::View Camera::getView() const
{
    return this->view;
}

sf::Vector2f Camera::getTopLeftCorner() const
{
    sf::Vector2f center = this->view.getCenter();
    sf::Vector2f size = this->view.getSize();

    sf::Vector2f topCorner;

    topCorner.x = center.x - size.x/2;
    topCorner.y = center.y - size.y/2;

    return topCorner;
}

sf::Vector2f Camera::getCenter() const
{
    return this->view.getCenter();
}

// setters
void Camera::setMapSize(sf::Vector2f mapSize)
{
    this->mapSize = mapSize;
}

// zoom in-out
void Camera::zoomEvent(int value)
{
    /*
    value:
    1 -> zoom in
    -1 -> zoom out
    */

    this->view.setSize(sf::Vector2f(this->windowSize.x,this->windowSize.y));

    if(value == 1) // zoom in
        {
            if(this->zoomModifier - this->valueModifier >= this->minView)
                this->zoomModifier -= this->valueModifier;
        }
    else
        {
            if(this->zoomModifier + this->valueModifier <= this->maxView)
                this->zoomModifier += this->valueModifier;
        }

    this->view.zoom(this->zoomModifier);
}

void Camera::handleView(Character character)
{
    sf::Vector2f playerPosition = character.getCharacterPosition();

    // to position camera on the map, not outside it, if camera is centred on character while he's being on map corners
    sf::Vector2f sizeCamera = this->view.getSize();
    float cameraXleft = playerPosition.x - sizeCamera.x / 2;
    float cameraXright = playerPosition.x + sizeCamera.x / 2;
    float cameraYup = playerPosition.y - sizeCamera.y / 2;
    float cameraYdown = playerPosition.y + sizeCamera.y / 2;

    this->view.setCenter(sf::Vector2f(playerPosition.x,playerPosition.y));

    if(cameraXleft < 0 || cameraYup < 0 || cameraXright > this->mapSize.x || cameraYdown > this->mapSize.y)
        {
            float moveX = 0, moveY=0;

            if(cameraXleft<0)
                moveX = -cameraXleft;
            if(cameraXright > this->mapSize.x)
                moveX = -(cameraXright - this->mapSize.x);

            if(cameraYup<0)
                moveY = -cameraYup;
            if(cameraYdown > this->mapSize.y)
                moveY = -(cameraYdown - this->mapSize.y);

            this->view.move(moveX,moveY);
        }
}

// constructors
Camera::Camera()
{
    std::string pathValues = "values/options/options.json";
    std::ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    this->windowSize.x = (data["windowSizeX"].is_null()?0:(float)data["windowSizeX"]);
    this->windowSize.y = (data["windowSizeY"].is_null()?0:(float)data["windowSizeY"]);

    this->view.setSize(sf::Vector2f(this->windowSize.x,this->windowSize.y));

    this->zoomModifier = 1.0; // default view

    this->valueModifier = 0.01;

    this->minView = 0.4;
    this->maxView = 1.2;
}

// destructors
Camera::~Camera()
{

}
