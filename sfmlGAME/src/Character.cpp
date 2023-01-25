#include "Character.h"

// revive
void Character::revive()
{
    this->setCharacterPosition(this->getSpawnPoint());
    this->setCurrentHealth(this->getHealth());
    this->setIsDead(false);
    this->setIsHit(false);
    this->setIsDamaging(false);
    this->setIsKnockbacked(false);
    this->setIsIdle(false);
    this->setIsMoving(false);
    this->setIsAttacking(false);
    this->setIsSpellCasting(false);
    this->setActionInProgress(false);
}

//getters
int Character::getEnemyDirection() const
{
    return this->enemyDirection;
}

int Character::getDirection() const
{
    return this->direction;
}

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

int Character::getSpeedMovement() const
{
    return this->speedMovement;
}

int Character::getSpeedAttack() const
{
    return this->speedAttack;
}

int Character::getBaseDamage() const
{
    return this->baseDamage;
}

bool Character::getIsDead() const
{
    return this->isDead;
}

bool Character::getIsDamaging() const
{
    return this->isDamaging;
}

bool Character::getIsHit() const
{
    return this->isHit;
}

bool Character::getDidChangeDirection() const
{
    return this->didChangeDirection;
}

bool Character::getActionInProgress() const
{
    return this->actionInProgress;
}

bool Character::getIsIdle() const
{
    return this->isIdle;
}

bool Character::getKnockback() const
{
    return this->knockback;
}

bool Character::getIsMoving() const
{
    return this->isMoving;
}

bool Character::getWalkIntoObstacle() const
{
    return this->walkIntoObstacle;
}

bool Character::getIsAttacking() const
{
    return this->isAttacking;
}

bool Character::getIsSpellCasting() const
{
    return this->isSpellCasting;
}

bool Character::getIsKnockbacked() const
{
    return this->isKnockbacked;
}

Vector2f Character::getCharacterPosition() const
{
    return this->characterPosition;
}

Vector2f Character::getCharacterSize() const
{
    return this->characterSize;
}

Vector2f Character::getSpawnPoint() const
{
    return this->spawnPoint;
}

float Character::getRadiusAttack() const
{
    return this->radiusAttack;
}

float Character::getKnockbackDistance() const
{
    return this->knockbackDistance;
}

//setters
void Character::setEnemyDirection(int enemyDirection)
{
    this->enemyDirection = enemyDirection;
}

void Character::setDirection(int direction)
{
    this->direction = direction;
}

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

void Character::setSpeedMovement(int speedMovement)
{
    this->speedMovement = speedMovement;
}

void Character::setSpeedAttack(int speedAttack)
{
    this->speedAttack = speedAttack;
}

void Character::setBaseDamage(int baseDamage)
{
    this->baseDamage = baseDamage;
}

void Character::setIsKnockbacked(bool isKnockbacked)
{
    this->isKnockbacked = isKnockbacked;
}

void Character::setWalkIntoObstacle(bool walkIntoObstacle)
{
    this->walkIntoObstacle = walkIntoObstacle;
}

void Character::setIsDamaging(bool isDamaging)
{
    this->isDamaging = isDamaging;
}

void Character::setKnockback(bool knockback)
{
    this->knockback = knockback;
}

void Character::setIsAttacking(bool isAttacking)
{
    this->isAttacking = isAttacking;
}

void Character::setDidChangeDirection(bool didChangeDirection)
{
    this->didChangeDirection = didChangeDirection;
}

void Character::setIsIdle(bool isIdle)
{
    this->isIdle = isIdle;
}

void Character::setIsMoving(bool isMoving)
{
    this->isMoving = isMoving;
}

void Character::setIsSpellCasting(bool isSpellCasting)
{
    this->isSpellCasting = isSpellCasting;
}

void Character::setActionInProgress(bool actionInProgress)
{
    this->actionInProgress = actionInProgress;
}

void Character::setIsHit(bool isHit)
{
    this->isHit = isHit;
}

void Character::setIsDead(bool isDead)
{
    this->isDead = isDead;
}

void Character::setSpawnPoint(Vector2f spawnPoint)
{
    this->spawnPoint = spawnPoint;
}

void Character::setCharacterPosition(Vector2f newPosition)
{
    this->characterPosition.x = newPosition.x;
    this->characterPosition.y = newPosition.y;
}

void Character::setCharacterSize(Vector2f characterSize)
{
    this->characterSize = characterSize;
}

void Character::setRadiusAttack(float radiusAttack)
{
    this->radiusAttack = radiusAttack;
}

void Character::setKnockbackDistance(float knockbackDistance)
{
    this->knockbackDistance = knockbackDistance;
}

//constructors
Character::Character(string fileName)
{
    // i can get these values from json file

    string pathValues = "values/characters/" + fileName + ".json";
    ifstream file(pathValues);
    nlohmann::json data = nlohmann::json::parse(file);

    float x = ((data["startPositionX"].is_null()==true)?0:(int)data["startPositionX"]);
    float y = ((data["startPositionY"].is_null()==true)?0:(int)data["startPositionY"]);
    this->setSpawnPoint(Vector2f(x,y));
    this->setCharacterPosition(Vector2f(x,y));

    this->direction = 3; // by default the character is facing downwards
    this->setActionInProgress(false);

    this->setHealth(data["health"].is_null()==true?0:(int)data["health"]);
    this->setMana(data["mana"].is_null()==true?0:(int)data["mana"]);
    this->setSpeedMovement(data["speedMovement"].is_null()==true?0:(int)data["speedMovement"]);
    this->setSpeedAttack(data["speedAttack"].is_null()==true?0:(int)data["speedAttack"]);
    this->setKnockback(data["knockback"].is_null()==true?0:(bool)data["knockback"]);
    this->setRadiusAttack(data["radiusAttack"].is_null()==true?0:(float)data["radiusAttack"]);

    this->setCurrentHealth(this->getHealth());

    this->setIsSpellCasting(false);
    this->setIsMoving(false);
    this->setIsAttacking(false);
    this->setIsIdle(false);
    this->setDidChangeDirection(false);
    this->setWalkIntoObstacle(false);
    this->setIsHit(false);
    this->setIsDamaging(false);
    this->setIsKnockbacked(false);
    this->setIsDead(false);

    this->setKnockbackDistance(50.0);
    this->setBaseDamage(25);
}

//destructors
Character::~Character()
{

}
