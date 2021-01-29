#include "Light.h"
#include "MatFuncs.h"

Light::Light(sf::Vector3f pos, sf::Vector3f dir)
{
	position = pos; direction = dir;
}

float Light::getLightning(sf::Vector3f pos)
{
	sf::Vector3f fark = position - pos;
	fark = sf::Vector3f(AbsolNumber(fark.x), AbsolNumber(fark.y), AbsolNumber(fark.z));
	float topFark = fark.x + fark.y + fark.z;
	return (1.0 / topFark) * 1.0;
}