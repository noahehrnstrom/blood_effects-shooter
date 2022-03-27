#ifndef enemyManager_hpp
#define enemyManager_hpp

#include <SFML/Graphics.hpp>
#include "bulletManager.hpp"
#include "explosionManager.hpp"

struct enemy
{
    sf::Vector2f pos;
    sf::Vector2f center;
    float ang;
    void create(sf::Vector2f _pos, sf::Vector2f _center)
    {
        center = _center;
        pos = _pos;
        sf::Vector2f dir = sf::Vector2f(center.x - _pos.x, center.y - _pos.y);
        ang = atan2f(dir.y, dir.x) / PI * 180.0f;
    }
    
    void update()
    {
        float difX = center.x - pos.x;
        float difY = center.y - pos.y;
        float dist = sqrt(difX * difX + difY * difY);
        if (dist > 150)
        {
            pos.x += cos(ang / 180.0 * PI);
            pos.y += sin(ang / 180.0 * PI);
        }
    }
};

class enemyManager
{
public:
    static std::vector<enemy*> enemies;
    static sf::Sprite enemySprite;
    static sf::Vector2i simulationSpace;
    static void init(sf::Texture& text, sf::Vector2i _simulationSpace);
    static void createEnemy(sf::Vector2f pos, float ang);
    static void drawEnemies(sf::RenderWindow& window);
};

#endif /* enemyManager_hpp */
