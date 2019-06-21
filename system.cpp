#pragma once
#include "stdafx.h"
#include "randomGen.h"
using namespace std;


SolarSystem::SolarSystem() {
	generateSystem();
	starsNum = 1;
}

void SolarSystem::generateSystem() {
	//do uzupelnienia
	star alpha;
	starContainer.push_back(alpha);

	planetNum = randomGen(0, maxPlanets);
	for (int i = 0; i < planetNum; i++) {
		planet beta(alpha);
		planetContainer.push_back(beta);
	

	}
	
}



void SolarSystem::drawSystem(sf::RenderWindow &window,shaderManager &shader) {
	//star draw
	shader.standardStarFragShader.setUniform("radiusToBrightness", (float)starContainer[0].radiusToBrightness);
	window.draw(starContainer[0].starLightObj, &shader.standardStarFragShader);
	//starContainer[0].starObj.setFillColor(sf::Color::Blue);
	window.draw(starContainer[0].starObj);
	//planets draw
	for (int i = 0; i < planetContainer.size(); i++) {
		window.draw(planetContainer[i].orbit);
		window.draw(planetContainer[i].planetObj, &shader.standardPlanetNoiseFragShader);

	//moons draw
		for (int y = 0; y < planetContainer[i].moonContainer.size(); y++) {
			window.draw(planetContainer[i].moonContainer[y].moonObj);
			window.draw(planetContainer[i].moonContainer[y].orbit, planetContainer[i].moonContainer[y].currentTransform);

	}
	}


}

void SolarSystem::updateSystem(sf::Clock &clock,int timeMul) {
	double sec = clock.getElapsedTime().asSeconds()*timeMul;
	clock.restart();
	//moons orbit update if necessery
	moonOrbitsUpdate();
	//planets and moons update
	for (int i = 0; i < planetContainer.size(); i++) {
		planetContainer[i].update(sec, starContainer[0]);
		for (int y = 0; y < planetContainer[i].moonContainer.size(); y++)
			planetContainer[i].moonContainer[y].update(sec, &planetContainer[i]);
		
	}

	//orbits update if necessery
	orbitsUpdate();
	


}

void SolarSystem::orbitsUpdate() {
	for (int i = 0; i < planetContainer.size(); i++) {
		if (planetContainer[i].traveledAngle > 360) {
			planetContainer[i].traveledAngle = 0;
			planetContainer[i].orbitCalculate(starContainer[0]);
			
		}

	}
}

void SolarSystem::moonOrbitsUpdate() {
	for (int i = 0; i < planetContainer.size(); i++) {
		for (int y = 0; y < planetContainer[i].moonContainer.size(); y++) {
			if (planetContainer[i].moonContainer[y].traveledAngle > 360) {
				planetContainer[i].moonContainer[y].traveledAngle = 0;
				planetContainer[i].moonContainer[y].orbitCalculate(&planetContainer[i]);

			}
		}
	}
}

void SolarSystem::drawPlanetaryLines(sf::RenderWindow &window) {
	sf::Vertex line[2];
	line[0].position.x = starContainer[0].positionX;
	line[0].position.y = starContainer[0].positionY;
	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;
	for (int i = 0; i < planetContainer.size(); i++) {
		line[1].position.x = planetContainer[i].positionX;
		line[1].position.y = planetContainer[i].positionY;
		window.draw(line, 2, sf::Lines);
	}


}

void SolarSystem::drawMoonLines(sf::RenderWindow &window) {
	sf::Vertex line[2];
	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;
	for (int i = 0; i < planetContainer.size(); i++) {
		line[0].position.x = planetContainer[i].positionX;
		line[0].position.y = planetContainer[i].positionY;
		for (int y = 0; y < planetContainer[i].moonContainer.size(); y++) {
			line[1].position.x = planetContainer[i].moonContainer[y].positionX;
			line[1].position.y = planetContainer[i].moonContainer[y].positionY;
			window.draw(line, 2, sf::Lines);
		}
	}


}
