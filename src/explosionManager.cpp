#include "explosionManager.hpp"

std::vector<explosion*> explosionManager::explosions;

sf::Sprite explosionManager::bloodSprite;
sf::RenderTexture explosionManager::blood;

void explosionManager::init(sf::Texture& text, sf::Vector2i simulationSpace)
{
    blood.create(simulationSpace.x, simulationSpace.y);
    blood.clear(sf::Color(86, 0, 0, 0));
    bloodSprite.setTexture(text);
    bloodSprite.setOrigin(text.getSize().x * 1 / 2.0, text.getSize().y * 1 / 2.0);
    bloodSprite.setColor(sf::Color(255, 255, 255, 175));
}

void explosionManager::updateExplosions()
{
    for (unsigned int i = 0; i < explosions.size(); i++)
    {
        auto& explosion = explosions[i];
        if (explosion->stage < 100)
        {
            explosion->update();
            explosion->stage++;
        }
        else
        {
            explosion->finish(bloodSprite, blood);
            explosions.erase(explosions.begin() + i);
            i -= 1;
        }
    }
}

void explosionManager::createExplosion(sf::Vector2f pos, sf::Vector2f dir)
{
    float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
    dir.x = dir.x / dist;
    dir.y = dir.y / dist;
    
    explosion* newExplosion = new explosion;
    newExplosion->create(pos, 0.75, sf::Vector2f(dir.x * 100, dir.y * 100));
    explosions.push_back(newExplosion);
}

void explosionManager::drawExplosions(sf::RenderWindow& window)
{
    sf::Sprite finish = sf::Sprite(blood.getTexture());
    finish.setPosition(0, 0);
    finish.setTextureRect(sf::IntRect(0, blood.getSize().y, blood.getSize().x, -blood.getSize().y));
    window.draw(finish);
    for (auto& explosion : explosions)
    {
        if (explosion->stage > 0 && explosion->stage < 101)
        {
            for (unsigned int c = 0; c < explosion->particlePositions.size(); c++)
            {
                sf::Vector2f pos = sf::Vector2f(explosion->pos.x + explosion->particlePositions[c].x, explosion->pos.y + explosion->particlePositions[c].y);
                bloodSprite.setPosition(pos);
                bloodSprite.setRotation(explosion->particleRots[c]);
                bloodSprite.setScale(1.3 * explosion->scale, 1.3 * explosion->scale);

                window.draw(bloodSprite);
            }
        }
    }
}
