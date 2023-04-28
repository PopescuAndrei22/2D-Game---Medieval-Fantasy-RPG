#include "AnimationManagement.h"

/* class methods */
Animation AnimationManagement::createAnimation(std::string animationName, nlohmann::json &data)
{
    Animation newAnimation;

    auto frameType = data.at("characterFrames");
    auto vectorFrames = frameType.at(0).at(animationName);

    for(unsigned i=0; i<vectorFrames.size(); i++)
        {
            sf::IntRect rect = sf::IntRect(vectorFrames[i][0],vectorFrames[i][1],vectorFrames[i][2],vectorFrames[i][3]);
            newAnimation.addFrame(rect,0.07f);
        }

    return newAnimation;
}

AnimationState AnimationManagement::characterAnimation(std::string fileName)
{
    std::string filePath = "sprites/characters/" + fileName + ".png";

    AnimationState animationState;
    animationState.setTexture(filePath);

    std::string pathValues = "values/characters/" + fileName + ".json";
    std::ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    try
        {
            // walk
            animationState.addAnimation("walkDown",this->createAnimation("walkDown",data));
            animationState.addAnimation("walkUp",this->createAnimation("walkUp",data));
            animationState.addAnimation("walkLeft",this->createAnimation("walkLeft",data));
            animationState.addAnimation("walkRight",this->createAnimation("walkRight",data));

            // idle
            animationState.addAnimation("idleDown",this->createAnimation("idleDown",data));
            animationState.addAnimation("idleUp",this->createAnimation("idleUp",data));
            animationState.addAnimation("idleLeft",this->createAnimation("idleLeft",data));
            animationState.addAnimation("idleRight",this->createAnimation("idleRight",data));

            // attack
            animationState.addAnimation("attackDown",this->createAnimation("attackDown",data));
            animationState.addAnimation("attackUp",this->createAnimation("attackUp",data));
            animationState.addAnimation("attackLeft",this->createAnimation("attackLeft",data));
            animationState.addAnimation("attackRight",this->createAnimation("attackRight",data));

            // spell cast
            animationState.addAnimation("spellCastDown",this->createAnimation("spellCastDown",data));
            animationState.addAnimation("spellCastUp",this->createAnimation("spellCastUp",data));
            animationState.addAnimation("spellCastLeft",this->createAnimation("spellCastLeft",data));
            animationState.addAnimation("spellCastRight",this->createAnimation("spellCastRight",data));

            // death
            animationState.addAnimation("death",this->createAnimation("death",data));
        }
    catch(const nlohmann::json::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    file.close();

    return animationState;
}

AnimationState AnimationManagement::objectAnimation(std::string fileName)
{
    // to modify here based on the level
    std::string filePath = "resources/maps/map1/map1_animations.png";

    AnimationState animationState;
    animationState.setTexture(filePath);

    std::string pathValues = "values/animatedObjects/" + fileName + ".json";
    std::ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    try
        {
            Animation newAnimation;

            auto frameType = data.at("objectFrames");
            auto vectorFrames = frameType.at(0);

            for(unsigned i=0; i<vectorFrames.size(); i++)
                {
                    sf::IntRect rect = sf::IntRect(vectorFrames[i][0],vectorFrames[i][1],vectorFrames[i][2],vectorFrames[i][3]);
                    newAnimation.addFrame(rect,0.07f);
                }

            // death
            animationState.addAnimation("object",newAnimation);
            animationState.setState("object");

        }
    catch(const nlohmann::json::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    file.close();

    return animationState;
}

AnimationState AnimationManagement::typeOfAnimation(std::string fileName, std::string animationType)
{
    if(animationType=="character")
        this->animationState = this->characterAnimation(fileName);
    else if(animationType=="object")
        this->animationState = this->objectAnimation(fileName);
    else
        std::cout<<"invalid type of animation"<<'\n';

    return this->animationState;
}

/* constructors */
AnimationManagement::AnimationManagement()
{

}

/* destructors */
AnimationManagement::~AnimationManagement()
{

}
