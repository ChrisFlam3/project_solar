#pragma once
#include <SFML/Graphics.hpp>
class camera {
public:
	sf::View view;
	long long unit;
	long double zoomin;
	long double zoomout;





	void update(sf::Event e);
	camera::camera();

};

