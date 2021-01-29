#include "QuickSFML.h"


QuickWindow::QuickWindow(sf::VideoMode videomode, std::string s,int frame)
	: window(videomode, s)
{
	window.setFramerateLimit(frame);
}

bool QuickWindow::isOpen() { return window.isOpen(); }


void QuickWindow::draw(sf::RenderWindow& w, sf::Image img, int zoom, sf::Vector2f pos, sf::Vector2f scale)
{
	sf::Texture resultTexture; resultTexture.loadFromImage(img);
	sf::Sprite resultSprite; resultSprite.setTexture(resultTexture);
	resultSprite.setPosition(pos/(float)zoom);
	resultSprite.scale(scale/(float)zoom);
	w.draw(resultSprite);
}


std::vector<sf::Event> QuickWindow::getEvents()
{
	std::vector<sf::Event> re;
	sf::Event e;
	while (window.pollEvent(e)) re.push_back(e);
	return re;
}

bool QuickWindow::pollEvent(sf::Event& event)
{
	return window.pollEvent(event);
}

void QuickWindow::clear(sf::Color color)
{
	window.clear(color);
}


void QuickWindow::display()
{
	window.display();
}

void QuickWindow::draw(sf::Image img,bool zoomLess, sf::Vector2f pos, sf::Vector2f scale)
{
	draw(window, img, zoomLess?1: zoom, pos, scale);
}

void QuickWindow::draw(sf::Sprite spr, bool zoomLess)
{
	spr.setScale(zoomLess ? spr.getScale(): spr.getScale() / (float)zoom);
	spr.setPosition(zoomLess ? spr.getPosition() : spr.getPosition() / (float)zoom);
	window.draw(spr);
}

void QuickWindow::draw(sf::Text txt, bool zoomLess)
{
	txt.setScale(zoomLess ? txt.getScale() : txt.getScale() / (float)zoom);
	txt.setPosition(zoomLess ? txt.getPosition() : txt.getPosition() / (float)zoom);
	window.draw(txt);
}

sf::RenderWindow* QuickWindow::getWindow()
{
	return &window;
}

void QuickWindow::close()
{
	window.close();
}

void QuickWindow::QuickEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window.close();
	}
}

void QuickWindow::setZoom(int z)
{
	zoom = z;
}

int QuickWindow::getZoom()
{
	return zoom;
}