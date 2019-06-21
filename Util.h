#pragma once
#include <SFML/Graphics.hpp>
#include "randomGen.h"
//note that class won't deliver graphical object nor set its position but store position in positionX,positionY
//note that class doesn't provide constructor and should be treated only as base class
//note that orbitCalculate should occur before update to maintain minimal error during calculations
class basePointOrbitObject {
public:
	long long positionX;
	long long positionY;
	long double velocity;
	long double mass;
	long double traveledAngle;
	long long timeStepDivide;
	long long vertexCountDivide;
	sf::VertexArray orbit;
	sf::Transform currentTransform;
	sf::Vector2 <long double> lastGravVec;
	sf::Vector2 <long double> velocityVec;
	sf::Vector2 <long double> lastObjectPos;



//template functions for any point-orbit object, source gravity object alpha have to provide alpha->mass,alpha->positionX,alpha->positionY 
template <typename AnyType>
void update(double sec, AnyType &alpha);
template <typename AnyType>
void orbitCalculate(AnyType &alpha);
//initialize all members, mass have to be provided along with initial distances from source mass and reference to source mass object 
template <typename AnyType>
void baseInitialize(AnyType &alpha, long double objectMass, const long long minObjectDistance, const long long maxObjectDistance);



};



template <typename AnyType>
void basePointOrbitObject::update(double sec, AnyType &alpha) {
	//add offset to maintain fixed coords with moving source mass
	sf::Vector2 <long double> diff;
	diff.x = alpha.positionX - lastObjectPos.x;
	diff.y = alpha.positionY - lastObjectPos.y;
	positionX += diff.x;
	positionY += diff.y;
	//calculate position using gravity acceleration and time interval
	long long distanceToStar = sqrt(pow(alpha.positionX - positionX, 2) + pow(alpha.positionY - positionY, 2));
	long double gravVelocity = G*alpha.mass / pow(distanceToStar, 2)*sec;
	sf::Vector2 <long double> gravVector((alpha.positionX - positionX) / (long double)distanceToStar*gravVelocity, (alpha.positionY - positionY) / (long double)distanceToStar*gravVelocity);
	velocityVec += gravVector;
	velocity = sqrt(pow(velocityVec.x, 2) + pow(velocityVec.y, 2));

	positionX += velocityVec.x*sec;
	positionY += velocityVec.y*sec;

	traveledAngle += acos(((-lastGravVec.x*(-gravVector.x)) + (-lastGravVec.y*(-gravVector.y))) / (sqrt(pow(lastGravVec.x, 2) + pow(lastGravVec.y, 2))*sqrt(pow(gravVector.x, 2) + pow(gravVector.y, 2)))) * 180 / PI;

	lastGravVec = gravVector;

	lastObjectPos.x = alpha.positionX;
	lastObjectPos.y = alpha.positionY;

	currentTransform.translate((sf::Vector2f)diff);


}

template <typename AnyType>
void basePointOrbitObject::orbitCalculate(AnyType &alpha) {
	orbit.clear();
	long long distanceToStar = sqrt(pow(alpha.positionX - positionX, 2) + pow(alpha.positionY - positionY, 2));
	int timeStep = distanceToStar / timeStepDivide;
	long double gravVelocity = G*alpha.mass / pow(distanceToStar, 2)*(timeStep / 2);
	sf::Vector2 <long double> gravVector((alpha.positionX - positionX) / (long double)distanceToStar*gravVelocity, (alpha.positionY - positionY) / (long double)distanceToStar*gravVelocity);
	int vertexCount = distanceToStar / vertexCountDivide;
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
		distanceToStar = sqrt(pow(alpha.positionX - pos.x, 2) + pow(alpha.positionY - pos.y, 2));
		gravVelocity = G*alpha.mass / pow(distanceToStar, 2)* timeStep;
		gravVector.x = (alpha.positionX - pos.x) / (long double)distanceToStar*gravVelocity;
		gravVector.y = (alpha.positionY - pos.y) / (long double)distanceToStar*gravVelocity;
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

template <typename AnyType>
void basePointOrbitObject::baseInitialize(AnyType &alpha, long double objectMass, const long long minObjectDistance, const long long maxObjectDistance) {
	mass = objectMass;
	double temp;
	temp = randomGen((long double)-1, (long double)1);
	temp = (temp > 0) ? 1 : -1;
	positionX = alpha.positionX + (randomGen(minObjectDistance, maxObjectDistance)*temp);
	temp = randomGen((long double)-1, (long double)1);
	temp = (temp > 0) ? 1 : -1;
	positionY = alpha.positionY + (randomGen(minObjectDistance, maxObjectDistance)*temp);


	//calculate min and max allowed velocity for orbit
	//first class space speed
	//second class space speed

	long long distanceToStar = sqrt(pow(alpha.positionX - positionX, 2) + pow(alpha.positionY - positionY, 2));

	long double vMin = sqrt(G*alpha->mass / distanceToStar);
	vMin = (long long)vMin;
	long double vMax = sqrt(2)*vMin*0.85;//max 85% to achive more stable orbits
	velocity = randomGen(vMin, vMax);

	//initial velocity vector
	sf::Vector2 <long long> cm(alpha.positionX - positionX, alpha.positionY - positionY);
	velocityVec.x = temp*cm.y / distanceToStar*velocity;
	velocityVec.y = temp*(-cm.x) / distanceToStar*velocity;

	long double gravVelocity = G*alpha.mass / pow(distanceToStar, 2);
	lastGravVec = sf::Vector2 <long double>((alpha.positionX - positionX) / (long double)distanceToStar*gravVelocity + 1000, (alpha.positionY - positionY) / (long double)distanceToStar*gravVelocity + 1000);//trash, just keeps initial acos in range
	traveledAngle = 720;




	lastObjectPos.x = alpha->positionX;
	lastObjectPos.y = alpha->positionY;

	timeStepDivide = 10000000;
	vertexCountDivide = 100000000;
}

