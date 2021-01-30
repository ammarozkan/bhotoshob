#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class QuickFunctions
{
public:
	bool static clickController(int posX, int posY, int sizeX, int sizeY, int clickX, int clickY);
	bool static clickController(sf::Sprite sprite, int clickX, int clickY);
	bool static clickController(sf::Vector2i position, sf::Vector2i size, sf::Vector2i clickPosition);
	bool static clickController(sf::Sprite sprite, sf::Vector2i clickPosition);
};

class QuickWindow
{
private:
	sf::RenderWindow window; int zoom = 1; sf::Vector2i position = sf::Vector2i(0,0);
public:
	QuickWindow(sf::VideoMode videomode, std::string title, int frame=60);
	bool isOpen();
	void setZoom(int z);
	int getZoom();
	void setPosition(sf::Vector2i pos);
	sf::Vector2i getPosition();
	void static draw(sf::RenderWindow& w, sf::Image img, int zoom = 1, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2f scale = sf::Vector2f(1, 1), sf::Vector2i camera_pos = sf::Vector2i(0,0));
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


class QuickBreak
{
private:
	sf::Vector2i first_click; bool clicking = false;
public:
	void click(sf::Vector2i click_pos);
	sf::Vector2i unclick(sf::Vector2i click_pos);
	sf::Vector2i update(sf::Vector2i click_pos);
};