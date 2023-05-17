#include "CombatSystem.h"

/* class methods */
float CombatSystem::getEuclidianDistance(sf::Vector2f a, sf::Vector2f b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) * 1.0);
}

void CombatSystem::update(Player &player, Enemy &enemy)
{
    if(player.getIsDead() == true && enemy.getCurrentState() == "agressive")
        {
            enemy.revive();
            return;
        }

    if(enemy.getIsDead() || enemy.getIsDying())
        {
            return;
        }

    float distance = this->getEuclidianDistance(enemy.getCharacterPosition(),enemy.getPlayerPosition());

    if(distance < enemy.getRadiusAttack())
        {
            if(enemy.getCurrentState() == "agressive")
                {
                    if(enemy.getIsDamaging())
                        {
                            player.setCurrentHealth(player.getCurrentHealth() - enemy.getBaseDamageMelee());

                            if(player.getIsKnockable())
                                {
                                    player.setIsKnockbacked(true);

                                    player.setReceivedKnockbackDistance(enemy.getKnockbackDistance());

                                    player.setDirectionKnockback(enemy.getDirection());
                                }

                            player.setIsDamaged(true);
                        }

                    enemy.setIsAttacking(true);
                }
        }

    if(distance < player.getRadiusAttack())
        {
            if(player.getIsDamaging())
                {
                    enemy.setCurrentHealth(enemy.getCurrentHealth() - player.getBaseDamageMelee());

                    if(enemy.getIsKnockable())
                        {
                            enemy.setIsKnockbacked(true);

                            enemy.setReceivedKnockbackDistance(player.getKnockbackDistance());

                            enemy.setDirectionKnockback(player.getDirection());
                        }

                    enemy.setIsDamaged(true);
                }
        }

    if(player.getCurrentHealth() <= 0)
        {
            player.setIsDying(true);
        }

    if(enemy.getCurrentHealth() <= 0)
        {
            enemy.setIsDying(true);
        }
}

void CombatSystem::updateProjectiles(Character &character, std::vector<Projectile> &projectiles)
{
    // will set it as variable for each character
    float baseMagicDamage = 120.0f;
    float projectileKnockback = 10.0f;

    for(unsigned i=0; i<projectiles.size(); i++)
        {
            // to consider the case when the projectile is deleted before doing this
            if(projectiles[i].isCollision(character.getCharacterPosition(),character.getCharacterSize()) && projectiles[i].getIsProjectileDamaging())
                {
                    projectiles[i].setHasReachedDestination(true);
                    projectiles[i].setIsProjectileDamaging(false);
                    projectiles[i].setTarget(sf::Vector2f(character.getCharacterPosition().x + (character.getCharacterSize().x/2),
                                                      character.getCharacterPosition().y + (character.getCharacterSize().y/2)));


                    character.setCurrentHealth(character.getCurrentHealth() - baseMagicDamage);

                    /*
                    if(player.getIsKnockable())
                        {
                            player.setIsKnockbacked(true);

                            player.setReceivedKnockbackDistance(enemy.getKnockbackDistance());

                            player.setDirectionKnockback(enemy.getDirection());
                        }
                    */

                    character.setIsDamaged(true);

                    projectiles[i].setIsProjectileDamaging(false);
                }
        }
}

/* constructors */
CombatSystem::CombatSystem()
{

}

/* destructors */
CombatSystem::~CombatSystem()
{

}
