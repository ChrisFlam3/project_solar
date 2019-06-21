#pragma once
#include "stdafx.h"
#include <vector>
#include "shader.h"
using namespace std;
class SolarSystem {
public:
	int starsNum;
	int planetNum;
	
	vector <star> starContainer;
	vector <planet> planetContainer;

	void orbitsUpdate();
	void moonOrbitsUpdate();
	void drawPlanetaryLines(sf::RenderWindow &window);
	void drawMoonLines(sf::RenderWindow &window);
	void drawSystem(sf::RenderWindow &window, shaderManager &shader);
	void updateSystem(sf::Clock &clock,int timeMul=1);
	SolarSystem();
private:
	void generateSystem();
};