#include <SFML/Graphics.hpp>
#include "explosionManager.hpp"
#include "resourceManager.hpp"
#include "enemyManager.hpp"
#include "cannon.hpp"

sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Blood Effect", sf::Style::Fullscreen);

int main(int argc, char** argv)
{
    bool mouseDown = false;
    resourceManager resources;
    window.setFramerateLimit(100);
    
    sf::Vector2i simulationSpace = sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    
    sf::Sprite backdrop;
    backdrop.setTexture(resources.getTexture(plains_texture));
    backdrop.setColor(sf::Color(255, 255, 255, 200));
    backdrop.setScale(simulationSpace.x / 700, simulationSpace.y / 393);
    
    explosionManager explosionmanager;
    explosionmanager.init(resources.getTexture(blood_texture), simulationSpace);
    
    bulletManager bulletmanager;
    bulletmanager.init(resources.getTexture(bullet_texture), simulationSpace);
    
    enemyManager enemymanager;
    enemymanager.init(resources.getTexture(enemy_texture), simulationSpace);
    
    cannon Cannon(resources.getTexture(cannon_texture), sf::Vector2f(simulationSpace.x / 2, simulationSpace.y / 2));
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mouseDown = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bulletmanager.createBullet(sf::Vector2f(Cannon.getPos().x + Cannon.getDir().x * 130, Cannon.getPos().y + Cannon.getDir().y * 130), Cannon.getDir());
                    Cannon.fire();

                    mouseDown = false;
                }
            }
        }
        
        if (mouseDown)
        {
            // Enables spraying
        }
        
        if (randomGenerator::getRandom<int>(0, 20) == 0)
        {
            float ang = randomGenerator::getRandom<float>(0, 359);
            enemymanager.createEnemy(sf::Vector2f( (simulationSpace.x / 2) + (simulationSpace.x * cos(ang / 180.0 * PI)), (simulationSpace.y / 2) + (simulationSpace.y * sin(ang / 180.0 * PI)) ), randomGenerator::getRandom<float>(0, 359));
        }
        
        window.clear(sf::Color::Black);
        window.draw(backdrop);
        explosionmanager.updateExplosions();
        explosionmanager.drawExplosions(window);
        bulletmanager.drawBullets(window);
        Cannon.draw(window, sf::Vector2f(sf::Mouse::getPosition(window)));
        enemymanager.drawEnemies(window);
        window.display();
    }
    return 0;
}
