#pragma once
#include <SFML/Graphics.hpp>
class star {
public:
	long long positionX;
	long long positionY;
	long double mass;
	long long radius;
	long long brightness;
	long double radiusToBrightness;
	sf::CircleShape starObj;
	sf::CircleShape starLightObj;
	star();
	
private:
	void generateStar();







};
