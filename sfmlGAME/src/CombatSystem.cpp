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

/* constructors */
CombatSystem::CombatSystem()
{

}

/* destructors */
CombatSystem::~CombatSystem()
{

}
