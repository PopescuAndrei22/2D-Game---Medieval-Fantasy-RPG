#include "Boss.h"

/* class methods */
void Boss::revive()
{
    this->Enemy::revive();
}

void Boss::setValues(std::string fileName)
{
    this->Enemy::setValues(fileName);

    std::string pathValues = "values/characters/" + fileName + ".json";
    std::ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    auto bossValues = data.at("bossValues");

    try
        {
            this->setEnemyName(bossValues["name"]);

        }
    catch(const nlohmann::json::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    file.close();
}

Boss::Boss()
{

}

Boss::~Boss()
{

}
