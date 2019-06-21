#pragma once
#include "stdafx.h"
#include "randomGen.h"
using namespace std;

star::star() {
	generateStar();
	//dynamic members allocation

}

void star::generateStar() {
	radius = randomGen(minStandardStarRadius, maxStandardStarRadius);
	positionX = randomGen((long long)-1000000000, (long long)1000000000);//UWAGA NA SZTYWNO 2MLD!!!!!
	positionY= randomGen((long long)-1000000000, (long long)1000000000);//UWAGA NA SZTYWNO 2MLD!!!!!
	mass = randomGen(MinStarMassPerMeterRadius*radius, MaxStarMassPerMeterRadius*radius);
	brightness = randomGen(radius * 1000,radius*2000);
	radiusToBrightness = (long double)radius / brightness;

	//graphical object initialization
	starObj.setRadius(radius);
	starObj.setPointCount(1000);
	starObj.setOrigin(radius, radius);
	starObj.setPosition(positionX, positionY);

	starLightObj.setRadius(brightness);
	starLightObj.setPointCount(1000);
	starLightObj.setOrigin(brightness, brightness);
	starLightObj.setPosition(positionX, positionY);
	starLightObj.setTextureRect(sf::IntRect(0, 0, 2048, 2048));


	
	
}