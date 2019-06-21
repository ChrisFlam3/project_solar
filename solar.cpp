#pragma once
#include "stdafx.h"
#include <windows.h>
#include "randomGen.h"
#include "textureHolder.h"
using namespace std;
int x = 0;
int main()
{

	shaderManager shader;
	textureHolder texHolder;


	sf::Clock clock;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	settings.sRgbCapable = false;
	sf::RenderWindow window(sf::VideoMode(1920, 1080,40U), "solar", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	camera cam;
	


	SolarSystem alpha;
	texHolder.generateSystemTextures(alpha, shader);
	texHolder.planetTexContainer[0].copyToImage().saveToFile("x.png");
	


	cam.view.setCenter(alpha.planetContainer[0].positionX, alpha.planetContainer[0].positionY);
	cout.setf(ios::fixed);
	cout << "star  radius  " << alpha.starContainer[0].radius/1000 << endl;
	cout << "planet0 radius " << alpha.planetContainer[0].radius / 1000 << " distance to star " << sqrt(pow(alpha.starContainer[0].positionX - alpha.planetContainer[0].positionX, 2) + pow(alpha.starContainer[0].positionY - alpha.planetContainer[0].positionY, 2))/1000<<endl;
	


	window.setView(cam.view);

	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			cam.update(event);
		}



	

		
	
		window.clear();
		alpha.updateSystem(clock,10000);
		//cam.view.setCenter(alpha.planetContainer[0].positionX, alpha.planetContainer[0].positionY);
		window.setView(cam.view);
		alpha.drawSystem(window, shader);
		alpha.drawPlanetaryLines(window);
		alpha.drawMoonLines(window);
		window.display();

		
		
		//cout << alpha.planetContainer[0].velocity << endl;
		//cout << "planets:  " << alpha.planetContainer.size() << endl;
		//cout << alpha.planetContainer[0].traveledAngle << endl;

	}

	return 0;
}