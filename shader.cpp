#include "shader.h"
shaderManager::shaderManager() {
	randomTexture.loadFromFile("dither.png");
	randomTexture.setRepeated(false);

	standardStarFragShader.loadFromFile("standardStarFragShader.frag", sf::Shader::Fragment);
	standardStarFragShader.setUniform("texture", randomTexture);

	standardPlanetNoiseFragShader.loadFromFile("standardPlanetNoiseFragShader.frag", sf::Shader::Fragment);

	textureGenShader.loadFromFile("textureGenShader.frag", sf::Shader::Fragment);

}