#ifndef ANIMATION_H
#define ANIMATION_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
    public:

        /* getters */
        sf::IntRect getFrame();
        unsigned int getFrameIndex() const;
        unsigned int getSize() const;
        bool getIsFinished() const;
        bool getIsLooped() const;

        /* setters */
        void setIsLooped(bool);

        /* class methods */
        // adding frames
        void addFrame(sf::IntRect, float);
        void play();
        void pause();
        void stop();
        void update(float);

        /* constructors */
        Animation();

        /* destructors */
        ~Animation();

    private:
        struct Frame
        {
            sf::IntRect rect; // the rectangle representing the desired frame
            float duration; // duration of a certain frame
        };

        std::vector<Frame> frames; // vector of frames

        float elapsedTime;

        bool isPlaying;

        bool isLooped;

        bool isFinished;

        unsigned int currentFrame;
};

#endif // ANIMATION_H
