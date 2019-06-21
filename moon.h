#pragma once
#include <SFML/Graphics.hpp>
class planet;
class moon {
public:

	long long radius;
	long double velocity;
	long double mass;
	long long positionX;
	long long positionY;
	long double traveledAngle;
	sf::Vector2 <long double> lastGravVec;
	sf::Vector2 <long double> velocityVec;
	sf::Vector2 <long double> lastPlanetPos;
	sf::VertexArray orbit;
	sf::CircleShape moonObj;
	sf::Transform currentTransform;


	moon(planet* const alpha);
	void update(double sec, planet* const alpha);
	void orbitCalculate(planet* const alpha);




private:
	void generateMoon(planet* const alpha);



};
