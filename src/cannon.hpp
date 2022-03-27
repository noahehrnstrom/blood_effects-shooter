#ifndef cannon_hpp
#define cannon_hpp

#include <SFML/Graphics.hpp>
#include "math.h"
#define PI 3.14159265359

class cannon
{
public:
    cannon(sf::Texture& text, sf::Vector2f pos);
    void draw(sf::RenderWindow& window, sf::Vector2f target);
    void fire();
    sf::Vector2f getPos() const { return cannonSprite.getPosition(); };
    sf::Vector2f getDir();
    float pointTowards(sf::Vector2f start, sf::Vector2f end);
private:
    sf::Sprite cannonSprite;
    sf::Vector2f origin;
    int firing;
};

#endif /* cannon_hpp */
