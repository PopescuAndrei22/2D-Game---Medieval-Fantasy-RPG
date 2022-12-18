#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Character.h"

using namespace sf;
using namespace std;

class Camera: public View
{
    public:

        void handleView(Character);

        void zoomEvent(int);

        // setters
        void setMapSize(Vector2f);

        //getters
        View getView() const;

        // constructors
        Camera();

        // destructors
        ~Camera();

    private:
        View view;

        float zoomValue;

        float zoomScaleValue,zoomMax,zoomMin;

        Vector2f windowSize;
        Vector2f mapSize;
};

#endif // CAMERA_H
