#include "textureHolder.h"
#define texSize 2048
void textureHolder::generateSystemTextures(SolarSystem &system,shaderManager &shader) {
	planetTexContainer.clear();
	sf::RenderTexture renderTexture;
	renderTexture.create(texSize, texSize);
	sf::RectangleShape temp;
	temp.setSize(sf::Vector2f(texSize, texSize));

	for (int i = 0; i < system.planetContainer.size(); i++) {
		shader.textureGenShader.setUniform("hashNum", (float)system.planetContainer[i].hash);
		renderTexture.clear();
		renderTexture.draw(temp,&shader.textureGenShader);
		renderTexture.display();

		planetTexContainer.push_back(renderTexture.getTexture());
	}
}