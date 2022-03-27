#include "cannon.hpp"

cannon::cannon(sf::Texture& text, sf::Vector2f pos)
{
    cannonSprite.setTexture(text);
    cannonSprite.setPosition(pos);
    cannonSprite.setScale(1.3, 1.3);
    origin = sf::Vector2f(text.getSize().x / 2 + 15, text.getSize().y / 2);
    firing = 0;
}

float cannon::pointTowards(sf::Vector2f start, sf::Vector2f end)
{
    sf::Vector2f dist = sf::Vector2f(end.x - start.x, end.y - start.y);
    return atan2f(dist.y, dist.x) / PI * 180.0;
}

void cannon::fire()
{
    firing = 30;
}

sf::Vector2f cannon::getDir()
{
    return sf::Vector2f(cos((cannonSprite.getRotation() - 90) / 180.0 * PI), sin((cannonSprite.getRotation() - 90) / 180.0 * PI));
}

void cannon::draw(sf::RenderWindow& window, sf::Vector2f target)
{
    cannonSprite.setOrigin(origin.x , origin.y - firing);
    cannonSprite.setRotation(pointTowards(sf::Vector2f(cannonSprite.getPosition().x, cannonSprite.getPosition().y), target)+90);
    window.draw(cannonSprite);
    if (firing > 0)
    {
        firing--;
    }
}
