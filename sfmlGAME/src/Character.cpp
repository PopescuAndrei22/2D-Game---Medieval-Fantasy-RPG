#include "Character.h"

/* getters */
int Character::getHealth() const
{
    return this->health;
}

int Character::getCurrentHealth() const
{
    return this->currentHealth;
}

int Character::getMana() const
{
    return this->mana;
}

int Character::getCurrentMana() const
{
    return this->currentMana;
}

int Character::getSpeedMovement() const
{
    return this->speedMovement;
}

int Character::getSpeedAttack() const
{
    return this->speedAttack;
}

int Character::getLeapsInDash() const
{
    return this->leapsInDash;
}

bool Character::getIsKnockable() const
{
    return this->isKnockable;
}

bool Character::getIsAttacking() const
{
    return this->isAttacking;
}

bool Character::getIsSpellCasting() const
{
    return this->isSpellCasting;
}

bool Character::getIsMoving() const
{
    return this->isMoving;
}

bool Character::getIsIdle() const
{
    return this->isIdle;
}

bool Character::getIsDashing() const
{
    return this->isDashing;
}

bool Character::getIsDamaging() const
{
    return this->isDamaging;
}

bool Character::getIsDamaged() const
{
    return this->isDamaged;
}

bool Character::getIsKnockbacked() const
{
    return this->isKnockbacked;
}

bool Character::getIsDying() const
{
    return this->isDying;
}

bool Character::getIsDead() const
{
    return this->isDead;
}

bool Character::getIsRespawnable() const
{
    return this->isRespawnable;
}

bool Character::getIsWalkingIntoObstacle() const
{
    return this->isWalkingIntoObstacle;
}

bool Character::getIsAbleToDash() const
{
    return this->isAbleToDash;
}

bool Character::getCooldownDash() const
{
    return this->cooldownDash;
}

bool Character::getRegenerableLife() const
{
    return this->regenerableLife;
}

float Character::getBaseDamageMelee() const
{
    return this->baseDamageMelee;
}

float Character::getKnockbackDistance() const
{
    return this->knockbackDistance;
}

float Character::getReceivedKnockbackDistance() const
{
    return this->receivedKnockbackDistance;
}

float Character::getRadiusAttack() const
{
    return this->radiusAttack;
}

float Character::getRespawnTime() const
{
    return this->respawnTime;
}

float Character::getLeapDistanceInDash() const
{
    return this->leapDistanceInDash;
}

std::string Character::getDirection() const
{
    return this->direction;
}

std::string Character::getDirectionKnockback() const
{
    return this->directionKnockback;
}

sf::Vector2f Character::getCharacterPosition() const
{
    return this->characterPosition;
}

sf::Vector2f Character::getSpawnPoint() const
{
    return this->spawnPoint;
}

sf::Vector2f Character::getCharacterSize() const
{
    return this->characterSize;
}

/* setters */
void Character::setHealth(int health)
{
    this->health = health;
}

void Character::setCurrentHealth(int currentHealth)
{
    this->currentHealth = currentHealth;
}

void Character::setMana(int mana)
{
    this->mana = mana;
}

void Character::setCurrentMana(int currentMana)
{
    this->currentMana = currentMana;
}

void Character::setSpeedMovement(int speedMovement)
{
    this->speedMovement = speedMovement;
}

void Character::setSpeedAttack(int speedAttack)
{
    this->speedAttack = speedAttack;
}

void Character::setLeapsInDash(int leapsInDash)
{
    this->leapsInDash = leapsInDash;
}

void Character::setIsKnockable(bool isKnockable)
{
    this->isKnockable = isKnockable;
}

void Character::setIsAttacking(bool isAttacking)
{
    this->isAttacking = isAttacking;
}

void Character::setIsSpellCasting(bool isSpellCasting)
{
    this->isSpellCasting = isSpellCasting;
}

void Character::setIsMoving(bool isMoving)
{
    this->isMoving = isMoving;
}

void Character::setIsIdle(bool isIdle)
{
    this->isIdle = isIdle;
}

void Character::setIsDashing(bool isDashing)
{
    this->isDashing = isDashing;
}

void Character::setIsDying(bool isDying)
{
    this->isDying = isDying;
}

void Character::setIsDead(bool isDead)
{
    this->isDead = isDead;
}

void Character::setIsRespawnable(bool isRespawnable)
{
    this->isRespawnable = isRespawnable;
}

void Character::setIsDamaging(bool isDamaging)
{
    this->isDamaging = isDamaging;
}

void Character::setIsDamaged(bool isDamaged)
{
    this->isDamaged = isDamaged;
}

void Character::setIsKnockbacked(bool isKnockbacked)
{
    this->isKnockbacked = isKnockbacked;
}

void Character::setIsWalkingIntoObstacle(bool isWalkingIntoObstacle)
{
    this->isWalkingIntoObstacle = isWalkingIntoObstacle;
}

void Character::setIsAbleToDash(bool isAbleToDash)
{
    this->isAbleToDash = isAbleToDash;
}

void Character::setCooldownDash(bool cooldownDash)
{
    this->cooldownDash = cooldownDash;
}

void Character::setRegenerableLife(bool regenerableLife)
{
    this->regenerableLife = regenerableLife;
}

void Character::setBaseDamageMelee(float baseDamageMelee)
{
    this->baseDamageMelee = baseDamageMelee;
}

void Character::setKnockbackDistance(float knockbackDistance)
{
    this->knockbackDistance = knockbackDistance;
}

void Character::setReceivedKnockbackDistance(float receivedKnockbackDistance)
{
    this->receivedKnockbackDistance = receivedKnockbackDistance;
}

void Character::setRadiusAttack(float radiusAttack)
{
    this->radiusAttack = radiusAttack;
}

void Character::setRespawnTime(float respawnTime)
{
    this->respawnTime = respawnTime;
}

void Character::setLeapDistanceInDash(float leapDistanceInDash)
{
    this->leapDistanceInDash = leapDistanceInDash;
}

void Character::setDirection(std::string direction)
{
    this->direction = direction;
}

void Character::setDirectionKnockback(std::string directionKnockback)
{
    this->directionKnockback = directionKnockback;
}

void Character::setCharacterPosition(sf::Vector2f characterPosition)
{
    this->characterPosition = characterPosition;
}

void Character::setSpawnPoint(sf::Vector2f spawnPoint)
{
    this->spawnPoint = spawnPoint;
}

void Character::setCharacterSize(sf::Vector2f characterSize)
{
    this->characterSize = characterSize;
}

/* class methods */
void Character::setValues(std::string fileName)
{
    std::string pathValues = "values/characters/" + fileName + ".json";
    std::ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    auto characterValues = data.at("characterValues");

    try
        {
            this->setHealth((int)characterValues["health"]);

            this->setMana((int)characterValues["mana"]);

            this->setIsKnockable((bool)characterValues["isKnockable"]);

            this->setBaseDamageMelee((float)characterValues["baseDamageMelee"]);

            this->setKnockbackDistance((float)characterValues["knockbackDistance"]);

            this->setSpeedMovement((int)characterValues["speedMovement"]);
            this->setSpeedAttack((int)characterValues["speedAttack"]);

            float xSpawn = (float)characterValues["spawnPoint"][0];
            float ySpawn = (float)characterValues["spawnPoint"][1];

            float xSize = (float)characterValues["characterSize"][0];
            float ySize = (float)characterValues["characterSize"][1];

            this->setRadiusAttack(characterValues["radiusAttack"]);

            this->setSpawnPoint(sf::Vector2f(xSpawn,ySpawn));

            this->setCharacterPosition(sf::Vector2f(xSpawn,ySpawn));

            this->setCharacterSize(sf::Vector2f(xSize,ySize));

            this->setRespawnTime((float)characterValues["respawnTime"]);

            this->setIsRespawnable((bool)characterValues["isRespawnable"]);

            this->setLeapDistanceInDash((float)characterValues["leapDistanceInDash"]);

            this->setLeapsInDash((int)characterValues["leapsInDash"]);

            this->setRegenerableLife((bool)characterValues["regenerableLife"]);

        }
    catch(const nlohmann::json::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    this->revive();


    file.close();
}

void Character::revive()
{
    this->setCharacterPosition(this->getSpawnPoint());

    this->setIsAttacking(false);
    this->setIsSpellCasting(false);
    this->setIsMoving(false);
    this->setIsIdle(true);
    this->setIsDashing(false);

    this->setIsDamaging(false);
    this->setIsDamaged(false);
    this->setIsKnockbacked(false);

    this->setIsDying(false);
    this->setIsDead(false);

    this->setIsAbleToDash(false);
    this->setCooldownDash(false);

    this->setReceivedKnockbackDistance(0.0f);

    this->setIsWalkingIntoObstacle(false);

    this->setDirection("down");

    this->setDirectionKnockback("down");

    this->setCurrentHealth(this->getHealth());

    this->setCurrentMana(this->getMana());
}

/* constructors */
Character::Character()
{

}

/* destructors */
Character::~Character()
{

}
