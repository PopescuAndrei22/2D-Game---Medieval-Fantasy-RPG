#include "Projectile.h"

bool Projectile::getHasReachedDestination() const
{
    return this->hasReachedDestination;
}

bool Projectile::getProjectileFinished() const
{
    return this->projectileFinished;
}

bool Projectile::getIsProjectileDamaging() const
{
    return this->isProjectileDamaging;
}

void Projectile::setPosition(sf::Vector2f position)
{
    this->animationStateProjectile.setPosition(position);
}

void Projectile::setTarget(sf::Vector2f target)
{
    this->target = target;
}

void Projectile::setHasReachedDestination(bool hasReachedDestination)
{
    this->hasReachedDestination = hasReachedDestination;
}

void Projectile::setProjectileFinished(bool projectileFinished)
{
    this->projectileFinished = projectileFinished;
}

void Projectile::setIsProjectileDamaging(bool isProjectileDamaging)
{
    this->isProjectileDamaging = isProjectileDamaging;
}

void Projectile::adjustDirection()
{
    sf::Vector2f vectorToTarget = this->target - this->animationStateProjectile.getPosition();
    float angleRadians = std::atan2(vectorToTarget.y, vectorToTarget.x);

    // Adjust the angle by 90 degrees to account for the initial downward orientation
    float angleDegrees = (angleRadians * (180 / 3.14159265)) + 90 + 180;

    this->animationStateProjectile.setRotation(angleDegrees);
}

void Projectile::moveTowardsTarget(float speed)
{
    sf::Vector2f currentPosition = this->animationStateProjectile.getPosition();
    sf::Vector2f direction = this->target - currentPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // to modify here, is based on the direction the projectile is initially facing
    if (distance - this->animationStateProjectile.getSize().y <= speed)
        {
            this->setHasReachedDestination(true);

            // Set the sprite's position to the target position
            this->animationStateProjectile.setPosition(target);
        }
    else
        {
            // Normalize the direction vector
            sf::Vector2f normalizedDirection = direction / distance;

            // Calculate the movement vector
            sf::Vector2f movement = normalizedDirection * speed;

            // Update the sprite's position
            this->animationStateProjectile.move(movement);
        }
}

void Projectile::moveProjectile(float timer)
{
    this->timeElapsed += timer;

    if(this->timeElapsed >= this->timeReset)
        {
            this->timeElapsed = 0.0f;
            this->moveTowardsTarget(2.0);
        }
}

bool Projectile::isCollision(sf::Vector2f entityPosition, sf::Vector2f entitySize)
{
    sf::Vector2f projectilePosition = this->animationStateProjectile.getPosition();
    sf::Vector2f projectileSize = this->animationStateProjectile.getSize();

    // Calculate the boundaries of the projectile's bounding box
    float projectileLeft = projectilePosition.x;
    float projectileRight = projectilePosition.x + projectileSize.x;
    float projectileTop = projectilePosition.y;
    float projectileBottom = projectilePosition.y + projectileSize.y;

    // Calculate the boundaries of the entity's bounding box
    float entityLeft = entityPosition.x;
    float entityRight = entityPosition.x + entitySize.x;
    float entityTop = entityPosition.y;
    float entityBottom = entityPosition.y + entitySize.y;

    // Check for collision
    if (projectileRight >= entityLeft && projectileLeft <= entityRight &&
        projectileBottom >= entityTop && projectileTop <= entityBottom) {
        // Collision detected
        return true;
    }

    // No collision detected
    return false;
}

void Projectile::update(float timer)
{
    if(this->getHasReachedDestination() == false)
        {
            this->animationStateProjectile.update(timer);
            this->moveProjectile(timer);
        }
    else
        {
            if(this->animationStateExplosion.getIsFinished() == true)
                {
                    this->setProjectileFinished(true);
                }

            // positioning the explosion
            sf::Vector2f explosionDimensions = this->animationStateExplosion.getSize();
            this->animationStateExplosion.setPosition(this->target.x - (explosionDimensions.x/2), this->target.y - (explosionDimensions.y/2));

            this->animationStateExplosion.update(timer);
        }
}

void Projectile::draw(sf::RenderWindow &window)
{
    if(this->getHasReachedDestination() == false)
        {
            window.draw(this->animationStateProjectile);
        }
    else
        {
            window.draw(this->animationStateExplosion);
        }
}

void Projectile::init(std::string projectileName)
{
    AnimationManagement ob;

    this->animationStateProjectile = ob.projectileAnimation(projectileName);

    // to modify here
    this->animationStateExplosion = ob.explosionAnimation("vortex");
    this->animationStateExplosion.setIsLooped(false);
}

Projectile::Projectile()
{
    this->timeElapsed = 0.0f;
    this->timeReset = 0.01f;

    this->setHasReachedDestination(false);
    this->setProjectileFinished(false);
    this->setIsProjectileDamaging(true);
}

Projectile::~Projectile()
{

}
