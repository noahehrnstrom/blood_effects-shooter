#ifndef bulletManager_hpp
#define bulletManager_hpp

#include <SFML/Graphics.hpp>
#include "randomGenerator.hpp"

struct bullet
{
    sf::Vector2f dir;
    float ang;
    sf::Vector2f pos;
    void create(sf::Vector2f _pos, sf::Vector2f _dir)
    {
        dir = sf::Vector2f(_dir.x * 20, _dir.y * 20);
        pos = _pos;
        ang = atan2f(_dir.y, _dir.x) / PI * 180.0f + 90;
    }
    void update()
    {
        pos += dir;
    }
};

class bulletManager
{
public:
    static std::vector<bullet*> bullets;
    static std::vector<sf::FloatRect> bulletBounds;
    static sf::Sprite bulletSprite;
    static sf::Vector2i simulationSpace;
    static void init(sf::Texture& text, sf::Vector2i _simulationSpace);
    static void createBullet(sf::Vector2f pos, sf::Vector2f dir);
    static void drawBullets(sf::RenderWindow& window);
};

#endif /* bulletManager_hpp */
