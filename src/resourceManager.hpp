#ifndef resourceManager_hpp
#define resourceManager_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

#define blood_texture 0
#define cannon_texture 1
#define bullet_texture 2
#define enemy_texture 3
#define plains_texture 4

class resourceManager
{
public:
    resourceManager();
    sf::Texture& getTexture(int texture);
private:
    std::vector<sf::Texture> textures;
    sf::Font font;
    std::vector<std::string> texturesToLoad;
};

#endif /* resourceManager_hpp */
