#pragma once

template <typename T1>
T1 AbsolNumber(T1 number)
{
	if (number < 0) return number * -1; else return number;
}

sf::Vector2f AbsolNumber(sf::Vector2f a)
{
	return sf::Vector2f(AbsolNumber(a.x), AbsolNumber(a.y));
}

float slop(sf::Vector2f p1, sf::Vector2f p2)
{
	sf::Vector2f p = AbsolNumber(p1 - p2);
	return p.y / p.x;
}