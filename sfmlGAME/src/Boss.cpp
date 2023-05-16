#include "Boss.h"

/* getters */
bool Boss::getProjectileRequest() const
{
    return this->projectileRequest;
}

/* setters */
void Boss::setBossName(std::string bossName)
{
    this->bossName = bossName;
}

void Boss::setProjectileRequest(bool projectileRequest)
{
    this->projectileRequest = projectileRequest;
}

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
            this->setBossName(bossValues["bossName"]);

        }
    catch(const nlohmann::json::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    file.close();
}

Boss::Boss()
{
    this->setProjectileRequest(false);
}

Boss::~Boss()
{

}
