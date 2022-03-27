#include "enemyManager.hpp"

std::vector<enemy*> enemyManager::enemies;
sf::Sprite enemyManager::enemySprite;
sf::Vector2i enemyManager::simulationSpace;

void enemyManager::init(sf::Texture& text, sf::Vector2i _simulationSpace)
{
    enemySprite.setTexture(text);
    enemySprite.setScale(0.75, 0.75);
    enemySprite.setOrigin(text.getSize().x / 2, text.getSize().y / 2);
    simulationSpace = _simulationSpace;
}

void enemyManager::createEnemy(sf::Vector2f pos, float ang)
{
    enemy* newEnemy = new enemy;
    newEnemy->create(pos, sf::Vector2f(simulationSpace.x / 2, simulationSpace.y / 2));
    enemies.push_back(newEnemy);
}

void enemyManager::drawEnemies(sf::RenderWindow& window)
{
    {
        for (unsigned int i = 0; i < enemies.size(); i++)
        {
            auto& enemy = enemies[i];
            
            enemy->update();
            enemySprite.setPosition(enemy->pos);
            enemySprite.setRotation(enemy->ang + 90);
            sf::FloatRect enemyBounds;
            enemyBounds.width = 45;
            enemyBounds.height = 45;
            enemyBounds.left = enemy->pos.x - 22.5;
            enemyBounds.top = enemy->pos.y - 22.5;
            
            bool shot = false;
            int bullet;
            
            for (bullet = 0; bullet < bulletManager::bulletBounds.size(); bullet++)
            {
                if (enemyBounds.intersects(bulletManager::bulletBounds[bullet]))
                {
                    shot = true;
                    break;
                }
            }

            if (shot)
            {
                explosionManager::createExplosion(enemy->pos, bulletManager::bullets[bullet]->dir);
                enemies.erase(enemies.begin() + i);
                i -= 1;
            }
            else
            {
                window.draw(enemySprite);
            }
        }
    }
}
