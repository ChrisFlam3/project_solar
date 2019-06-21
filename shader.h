#pragma once
#include <SFML/Graphics.hpp>
class shaderManager {
public:
	shaderManager();
	sf::Shader standardStarFragShader;
	sf::Shader standardPlanetNoiseFragShader;
	sf::Shader textureGenShader;
	sf::Texture randomTexture;
private:
	shaderManager(shaderManager& other) {}
	shaderManager& operator=(shaderManager& other) {}

};

