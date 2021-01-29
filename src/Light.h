#pragma once
#include <SFML/Graphics.hpp>

class Light
{
public:
	sf::Vector3f position, direction;

	Light(sf::Vector3f position, sf::Vector3f direction);
	float getLightning(sf::Vector3f pos);
};

