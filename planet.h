#pragma once
#include "star.h"
#include "moon.h"
#include <vector>
class planet {
public:
	long long radius;
	long double velocity;
	long double mass;
	long long positionX;
	long long positionY;
	long double hash;
	long double traveledAngle;
	int moonNum;
	std::vector <moon> moonContainer;
	sf::Vector2 <long double> lastGravVec;
	sf::Vector2 <long double> velocityVec;
	sf::VertexArray orbit;
	sf::CircleShape planetObj;

	planet(star alpha);
	void update(double sec,const star &alpha);
	void orbitCalculate(const star &alpha);




private:
	void generatePlanet(star alpha);



};