#include "bulletManager.hpp"

std::vector<bullet*> bulletManager::bullets;
std::vector<sf::FloatRect> bulletManager::bulletBounds;
sf::Sprite bulletManager::bulletSprite;
sf::Vector2i bulletManager::simulationSpace;

void bulletManager::init(sf::Texture& text, sf::Vector2i _simulationSpace)
{
    bulletSprite.setTexture(text);
    bulletSprite.setScale(1.3, 1.3);
    bulletSprite.setOrigin(text.getSize().x / 2, text.getSize().y / 2);
    simulationSpace = _simulationSpace;
}

void bulletManager::drawBullets(sf::RenderWindow& window)
{
    bulletBounds.clear();
    for (unsigned int i = 0; i < bullets.size(); i++)
    {
        auto& bullet = bullets[i];
        if (bullet->pos.x < 0 || bullet->pos.y < 0 || bullet->pos.x > simulationSpace.x || bullet->pos.y > simulationSpace.y)
        {
            bullets.erase(bullets.begin() + i);
            i -= 1;
        }
        else
        {
            bullet->update();
            bulletSprite.setPosition(bullet->pos);
            bulletSprite.setRotation(bullet->ang);
            
            bulletBounds.push_back(bulletSprite.getGlobalBounds());

            window.draw(bulletSprite);
        }
    }
}

void bulletManager::createBullet(sf::Vector2f pos, sf::Vector2f dir)
{
    bullet* newBullet = new bullet;
    newBullet->create(pos, sf::Vector2f(dir.x * 1, dir.y * 1));
    bullets.push_back(newBullet);
}
