#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "system.h"
using namespace std;

class textureHolder {
public:
	vector <sf::Texture> planetTexContainer;


	void generateSystemTextures(SolarSystem &system, shaderManager &shader);







};