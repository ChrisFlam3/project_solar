#pragma once
#include "stdafx.h"
#include "randomGen.h"
#include <iostream>
using namespace std;

planet::planet(star alpha) {
	generatePlanet(alpha);

	moonNum = randomGen(0, maxMoons);
	for (int i = 0; i < moonNum; i++) {
		moon alpha(this);
		moonContainer.push_back(alpha);
	}

}

void planet::generatePlanet(star alpha) {
	radius = randomGen(minPlanetRadius, maxPlanetRadius);
	mass = randomGen(MinPlanetMassPerMeterRadius*radius, MaxPlanetMassPerMeterRadius*radius);
	double temp;
	temp=randomGen((long double)-1, (long double)1);
	temp = (temp > 0) ? 1 : -1;
		positionX = alpha.positionX + (randomGen(minDistance, maxDistance)*temp);
	temp = randomGen((long double)-1, (long double)1);
	temp = (temp > 0) ? 1 : -1;
		positionY = alpha.positionY + (randomGen(minDistance, maxDistance)*temp);
		

	//calculate min and max allowed velocity for orbit
	//first class space speed
	//second class space speed

	long long distanceToStar = sqrt(pow(alpha.positionX - positionX, 2) + pow(alpha.positionY - positionY, 2));

	long double vMin = sqrt(G*alpha.mass/distanceToStar);
	vMin = (long long)vMin;
	long double vMax = sqrt(2)*vMin*0.85;//max 85% to achive more stable orbits
	velocity = randomGen(vMin, vMax);

	//initial velocity vector
	sf::Vector2 <long long> cm(alpha.positionX-positionX,alpha.positionY-positionY);
	velocityVec.x = temp*cm.y/distanceToStar*velocity;
	velocityVec.y = temp*(-cm.x) / distanceToStar*velocity;

	long double gravVelocity = G*alpha.mass / pow(distanceToStar, 2);
	lastGravVec=sf::Vector2 <long double>((alpha.positionX - positionX) / (long double)distanceToStar*gravVelocity+1000, (alpha.positionY - positionY) / (long double)distanceToStar*gravVelocity+1000);//trash, just keeps initial acos in range
	traveledAngle = 720;

	//graphical object initialization
	planetObj.setRadius(radius);
	planetObj.setPointCount(1000);
	planetObj.setOrigin(radius, radius);
	planetObj.setPosition(positionX, positionY);
	planetObj.setTextureRect(sf::IntRect(0, 0, 2048, 2048));

	//hash for texture generation
	hash = randomGen((long double)0, 100000);
}


void planet::update(double sec,const star &alpha) {
	//calculate position using gravity acceleration and time interval
	long long distanceToStar = sqrt(pow(alpha.positionX - positionX, 2) + pow(alpha.positionY - positionY, 2));
	long double gravVelocity = G*alpha.mass / pow(distanceToStar, 2)*sec;
	sf::Vector2 <long double> gravVector((alpha.positionX - positionX)/ (long double)distanceToStar*gravVelocity, (alpha.positionY - positionY)/ (long double)distanceToStar*gravVelocity);
	velocityVec += gravVector;
	velocity = sqrt(pow(velocityVec.x, 2) + pow(velocityVec.y, 2));
	
	positionX += velocityVec.x*sec;
	positionY += velocityVec.y*sec;
	
	traveledAngle += acos(((-lastGravVec.x*(-gravVector.x)) + (-lastGravVec.y*(-gravVector.y))) / (sqrt(pow(lastGravVec.x, 2) + pow(lastGravVec.y, 2))*sqrt(pow(gravVector.x, 2) + pow(gravVector.y, 2)))) * 180 / PI;

	lastGravVec = gravVector;

	planetObj.setPosition(positionX, positionY);
}

void planet::orbitCalculate(const star &alpha) {
	orbit.clear();
	long long distanceToStar = sqrt(pow(alpha.positionX - positionX, 2) + pow(alpha.positionY - positionY, 2));
	int timeStep = distanceToStar / 10000000;
	long double gravVelocity = G*alpha.mass / pow(distanceToStar, 2)*(timeStep/2);
	sf::Vector2 <long double> gravVector((long double)(alpha.positionX - positionX) / distanceToStar*gravVelocity, (long double)(alpha.positionY - positionY) / distanceToStar*gravVelocity);
	int vertexCount = distanceToStar / 100000000;
	sf::Vector2 <long long> pos(positionX, positionY);
	double angleStep = (double)360 / vertexCount;
	long double lastAngle = 0;
	long double traveledAngle=0;
	orbit.setPrimitiveType(sf::LineStrip);
	sf::Vector2 <long double> velVec = velocityVec;
	orbit.append(sf::Vertex((sf::Vector2f)pos));
	int index = 1;
	sf::Vector2 <long double> vec1=-gravVector;
	velVec += gravVector;
	pos.x += velVec.x * timeStep;
	pos.y += velVec.y * timeStep;

	while (traveledAngle<360){
		distanceToStar = sqrt(pow(alpha.positionX - pos.x, 2) + pow(alpha.positionY - pos.y, 2));
		gravVelocity = G*alpha.mass / pow(distanceToStar, 2)* timeStep;
		gravVector.x = (alpha.positionX - pos.x) / (long double)distanceToStar*gravVelocity;
		gravVector.y= (alpha.positionY - pos.y) / (long double)distanceToStar*gravVelocity;
		velVec += gravVector;
	
		pos.x += velVec.x * timeStep;
		pos.y += velVec.y * timeStep;
		gravVector = -gravVector;

	

		traveledAngle += acos(((vec1.x*gravVector.x)+(vec1.y*gravVector.y))/(sqrt(pow(vec1.x,2)+pow(vec1.y,2))*sqrt(pow(gravVector.x, 2) + pow(gravVector.y, 2))))*180/PI;


		
		if (traveledAngle > lastAngle + angleStep) {
			lastAngle = traveledAngle;
			orbit.append(  sf::Vertex((sf::Vector2f)pos));
			index++;
	}
		vec1 = gravVector;
	}



}


