#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Character.h"

using namespace sf;
using namespace std;

class Camera
{
    public:
        //getters
        View getView() const;
        Vector2f getTopLeftCorner() const;

        // setters
        void setMapSize(Vector2f);

        // centering the camera on the character
        void handleView(Character);

        // zoom in and out
        void zoomEvent(int);

        // constructors
        Camera();

        // destructors
        ~Camera();

    private:
        View view;

        Vector2f windowSize;
        Vector2f mapSize;

        float zoomModifier; // the current zoom value for view
        float valueModifier; // the quantity we decrease/increase the zoom modifier value
        float minView,maxView; // borders of the zoomModifier value
};

#endif // CAMERA_H
