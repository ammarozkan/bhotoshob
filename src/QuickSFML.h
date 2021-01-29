#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class QuickWindow
{
private:
	sf::RenderWindow window; int zoom = 1;
public:
	QuickWindow(sf::VideoMode videomode, std::string title, int frame=60);
	bool isOpen();
	void setZoom(int z);
	int getZoom();
	void static draw(sf::RenderWindow& w, sf::Image img, int zoom = 1, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2f scale = sf::Vector2f(1, 1));
	void draw(sf::Image img, bool zoomLess = false, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2f scale = sf::Vector2f(1, 1));
	void draw(sf::Sprite spr,bool zoomLess = false);
	void draw(sf::Text txt, bool zoomLess = false);
	sf::RenderWindow* getWindow();

	/* Event */
	std::vector<sf::Event> getEvents();
	bool pollEvent(sf::Event &event);
	void QuickEvents();


	void close();
	void clear(sf::Color color = sf::Color(0,0,0,255));
	void display();
};