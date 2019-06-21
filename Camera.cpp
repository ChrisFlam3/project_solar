#pragma once
#include "Camera.h"
using namespace std;
camera::camera() {
	view.setSize(1920, 1080);
	view.setCenter(960, 540);
	unit = 10;
	zoomin = 0.1;
	zoomout = 0.1;
}

void camera::update(sf::Event e) {
	if (e.type == sf::Event::KeyPressed) {
		switch (e.key.code) {//tymczasowo przesuwanie kamery do testów

		case sf::Keyboard::A:
			view.move(-unit, 0);
			break;

		case sf::Keyboard::D:
			view.move(unit, 0);
			break;

		case sf::Keyboard::W:
			view.move(0, -unit);
			break;

		case sf::Keyboard::S:
			view.move(0, unit);
			break;
		}
	}
	else if (e.type == sf::Event::MouseWheelScrolled) {
		if (e.mouseWheelScroll.delta >= 1) {
			if(zoomin<0.5)zoomin += 0.01;
			zoomout =0.1;
			
			if (view.getSize().x*(1 - zoomin) < 1920)//max zoom
				view.setSize(1920, 1080);
			else
				view.zoom(1-zoomin);
		
			
		}
		else{
			if(zoomout<0.5)zoomout += 0.01;
			zoomin = 0.1;
			if (view.getSize().x*(1 + zoomout) > 10000000000000000)//min zoom
				view.setSize(10000000000, 0.5625 * 10000000000);
			else
			view.zoom(1 + zoomout);
		}


	}


	unit = view.getSize().x / 1920*20;
	
}