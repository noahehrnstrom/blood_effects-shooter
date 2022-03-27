#ifndef exploisonManager_hpp
#define exploisonManager_hpp

#pragma warning(disable:4146)

#include <SFML/Graphics.hpp>
#include "randomGenerator.hpp"
#include <iostream>

struct explosion
{
    std::vector<sf::Vector2f> particlePositions;
    std::vector<sf::Vector2f> particleVel;
    std::vector<float> particleRots;
    std::vector<float> particleRotVels;
    float scale;
    
    sf::Vector2f pos;
    int stage = 0;
    
    void create(sf::Vector2f _pos, float _scale, sf::Vector2f dir)
    {
        pos = _pos;
        scale = _scale;
        for (unsigned int i = 0; i < 100; i++)
        {
            sf::Vector2f vel = sf::Vector2f(randomGenerator::getRandom<float>(-100, 100), randomGenerator::getRandom<float>(-100, 100));
            
            float dist = sqrt((vel.x * vel.x) + (vel.y * vel.y));
            float multiply = randomGenerator::getRandom<float>(0, 100);
            
            particleVel.push_back(sf::Vector2f((vel.x * multiply / dist + (dir.x * (multiply / 50))) / 13 * scale, (vel.y * multiply / dist + (dir.y * (multiply / 50))) / 13 * scale));
            particlePositions.push_back(sf::Vector2f(0, 0));
            particleRots.push_back(randomGenerator::getRandom<float>(0, 359));
            particleRotVels.push_back(randomGenerator::getRandom<float>(-5, 5));
        }
    }
    
    void finish(sf::Sprite& splat, sf::RenderTexture& blood)
    {
        for (unsigned int i = 0; i < particlePositions.size(); i++)
        {
            sf::Vector2f splatPos = sf::Vector2f(pos.x + particlePositions[i].x, pos.y + particlePositions[i].y);
            splat.setPosition(splatPos);
            splat.setRotation(particleRots[i]);
            splat.setScale(1.3 * scale, 1.3 * scale);

            blood.draw(splat);
        }
    }
    
    void update()
    {
        for (unsigned int i = 0; i < particleVel.size(); i++)
        {
            particleVel[i].x *= 0.95;
            particleVel[i].y *= 0.95;
            particleRots[i] += particleRotVels[i];
            particleRotVels[i] *= 0.95;
            particlePositions[i].x += particleVel[i].x;
            particlePositions[i].y += particleVel[i].y;
        }
    }
};

class explosionManager
{
public:
    static sf::RenderTexture blood;
    static std::vector<explosion*> explosions;
    static sf::Sprite bloodSprite;
    static void init(sf::Texture& text, sf::Vector2i simulationSpace);
    static void createExplosion(sf::Vector2f pos, sf::Vector2f dir);
    static void updateExplosions();
    static void drawExplosions(sf::RenderWindow& window);
};

#endif /* exploisonManager_hpp */
