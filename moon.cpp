#pragma once
#include "moon.h"
#include "randomGen.h"
#include "constants.h"
#include "planet.h"
#include <iostream>
using namespace std;
moon::moon(planet* const alpha) {
	generateMoon(alpha);
}

void moon::generateMoon(planet* const alpha) {
	radius = randomGen(minMoonRadius, maxMoonRadius);
	mass = randomGen(MinPlanetMassPerMeterRadius*radius, MaxPlanetMassPerMeterRadius*radius);
	double temp;
	temp = randomGen((long double)-1, (long double)1);
	temp = (temp > 0) ? 1 : -1;
	positionX = alpha->positionX + (randomGen(minMoonDistance, maxMoonDistance)*temp);
	temp = randomGen((long double)-1, (long double)1);
	temp = (temp > 0) ? 1 : -1;
	positionY = alpha->positionY + (randomGen(minMoonDistance, maxMoonDistance)*temp);


	//calculate min and max allowed velocity for orbit
	//first class space speed
	//second class space speed

	long long distanceToStar = sqrt(pow(alpha->positionX - positionX, 2) + pow(alpha->positionY - positionY, 2));

	long double vMin = sqrt(G*alpha->mass / distanceToStar);
	vMin = (long long)vMin;
	long double vMax = sqrt(2)*vMin*0.85;//max 85% to achive more stable orbits
	velocity = randomGen(vMin, vMax);

	//initial velocity vector
	sf::Vector2 <long long> cm(alpha->positionX - positionX, alpha->positionY - positionY);
	velocityVec.x = temp*cm.y / distanceToStar*velocity;
	velocityVec.y = temp*(-cm.x) / distanceToStar*velocity;

	long double gravVelocity = G*alpha->mass / pow(distanceToStar, 2);
	lastGravVec = sf::Vector2 <long double>((alpha->positionX - positionX) / (long double)distanceToStar*gravVelocity + 1000, (alpha->positionY - positionY) / (long double)distanceToStar*gravVelocity + 1000);//trash, just keeps initial acos in range
	traveledAngle = 720;

	//graphical object initialization
	moonObj.setRadius(radius);
	moonObj.setPointCount(1000);
	moonObj.setOrigin(radius, radius);
	moonObj.setPosition(positionX, positionY);


	lastPlanetPos.x = alpha->positionX;
	lastPlanetPos.y = alpha->positionY;
}


void moon::update(double sec,planet* const alpha) {
	//move by offset before calculations
	sf::Vector2 <long double> diff;
	diff.x = alpha->positionX - lastPlanetPos.x;
	diff.y = alpha->positionY - lastPlanetPos.y;
	positionX += diff.x;
	positionY += diff.y;
	//calculate position using gravity acceleration and time interval
	long long distanceToStar = sqrt(pow(alpha->positionX - positionX, 2) + pow(alpha->positionY - positionY, 2));
	long double gravVelocity = G*alpha->mass / pow(distanceToStar, 2)*sec;
	sf::Vector2 <long double> gravVector((alpha->positionX - positionX) / (long double)distanceToStar*gravVelocity, (alpha->positionY - positionY) / (long double)distanceToStar*gravVelocity);
	velocityVec += gravVector;
	velocity = sqrt(pow(velocityVec.x, 2) + pow(velocityVec.y, 2));

	positionX += velocityVec.x*sec;
	positionY += velocityVec.y*sec;
	
	traveledAngle += acos(((-lastGravVec.x*(-gravVector.x)) + (-lastGravVec.y*(-gravVector.y))) / (sqrt(pow(lastGravVec.x, 2) + pow(lastGravVec.y, 2))*sqrt(pow(gravVector.x, 2) + pow(gravVector.y, 2)))) * 180 / PI;

	lastGravVec = gravVector;


	moonObj.setPosition(positionX, positionY);
	

	lastPlanetPos.x = alpha->positionX;
	lastPlanetPos.y = alpha->positionY;
	//update offset for orbits draw
	currentTransform.translate((sf::Vector2f)diff);
}

void moon::orbitCalculate(planet* const alpha) {
	orbit.clear();
	long long distanceToStar = sqrt(pow(alpha->positionX - positionX, 2) + pow(alpha->positionY - positionY, 2));
	int timeStep = distanceToStar / 200000;
	long double gravVelocity = G*alpha->mass / pow(distanceToStar, 2)*(timeStep/2 );
	sf::Vector2 <long double> gravVector((alpha->positionX - positionX) / (long double)distanceToStar*gravVelocity, (alpha->positionY - positionY) / (long double)distanceToStar*gravVelocity);
	int vertexCount = distanceToStar / 100000;
	sf::Vector2 <long long> pos(positionX, positionY);
	double angleStep = (double)360 / vertexCount;
	long double lastAngle = 0;
	long double traveledAngle = 0;
	orbit.setPrimitiveType(sf::LineStrip);
	sf::Vector2 <long double> velVec = velocityVec;
	orbit.append(sf::Vertex((sf::Vector2f)pos));
	int index = 1;
	sf::Vector2 <long double> vec1 = -gravVector;
	velVec += gravVector;
	pos.x += velVec.x * timeStep;
	pos.y += velVec.y * timeStep;

	while (traveledAngle<360) {
		distanceToStar = sqrt(pow(alpha->positionX - pos.x, 2) + pow(alpha->positionY - pos.y, 2));
		gravVelocity = G*alpha->mass / pow(distanceToStar, 2)* timeStep;
		gravVector.x = (alpha->positionX - pos.x) / (long double)distanceToStar*gravVelocity;
		gravVector.y = (alpha->positionY - pos.y) / (long double)distanceToStar*gravVelocity;
		velVec += gravVector;

		pos.x += velVec.x * timeStep;
		pos.y += velVec.y * timeStep;
		gravVector = -gravVector;
		


		traveledAngle += acos(((vec1.x*gravVector.x) + (vec1.y*gravVector.y)) / (sqrt(pow(vec1.x, 2) + pow(vec1.y, 2))*sqrt(pow(gravVector.x, 2) + pow(gravVector.y, 2)))) * 180 / PI;


		if (traveledAngle > lastAngle + angleStep) {
			lastAngle = traveledAngle;
			orbit.append(sf::Vertex((sf::Vector2f)pos));
			index++;
		}
		vec1 = gravVector;
	}

	//reset planet offset
	currentTransform = sf::Transform();
}