#include "resourceManager.hpp"


resourceManager::resourceManager()
{
    texturesToLoad.push_back("textures/blood.png");
    texturesToLoad.push_back("textures/cannon.png");
    texturesToLoad.push_back("textures/bullet.png");
    texturesToLoad.push_back("textures/enemy.png");
    texturesToLoad.push_back("textures/plains.png");

    sf::Texture textureLoader;
    
    for (auto i : texturesToLoad)
    {
        if(!textureLoader.loadFromFile(i))
        {
            std::cout << "Failed to load game files" << std::endl;
            exit(0);
        }
        
        textures.push_back(textureLoader);
    }
}

sf::Texture& resourceManager::getTexture(int texture)
{
    return textures[texture];
}
