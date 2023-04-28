#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Character.h"

class Camera
{
    public:
        //getters
        sf::View getView() const;
        sf::Vector2f getTopLeftCorner() const;
        sf::Vector2f getCenter() const;

        // setters
        void setMapSize(sf::Vector2f);

        // centering the camera on the character
        void handleView(Character);

        // zoom in and out
        void zoomEvent(int);

        // constructors
        Camera();

        // destructors
        ~Camera();

    private:
        sf::View view;

        sf::Vector2f windowSize;
        sf::Vector2f mapSize;

        float zoomModifier; // the current zoom value for view
        float valueModifier; // the quantity we decrease/increase the zoom modifier value
        float minView,maxView; // borders of the zoomModifier value
};

#endif // CAMERA_H
