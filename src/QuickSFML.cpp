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


/* Functions */


bool QuickFunctions::clickController(int posX, int posY, int sizeX, int sizeY, int clickX, int clickY)
{
	return posX <= clickX && posX + sizeX >= clickX && posY <= clickY && posY + sizeY >= clickY;
}

bool QuickFunctions::clickController(sf::Sprite sprite, int clickX, int clickY)
{
	return clickController(sprite.getPosition().x, sprite.getPosition().y, sprite.getTexture()->getSize().x * sprite.getScale().x, sprite.getTexture()->getSize().y * sprite.getScale().y, clickX, clickY);
}

bool QuickFunctions::clickController(sf::Vector2i p, sf::Vector2i s, sf::Vector2i cp)
{
	return clickController(p.x, p.y, s.x, s.y, cp.x, cp.y);
}

bool QuickFunctions::clickController(sf::Sprite s, sf::Vector2i clickPosition)
{
	return clickController(s.getPosition().x, s.getPosition().y, s.getTexture()->getSize().x * s.getScale().x, s.getTexture()->getSize().y * s.getScale().y, clickPosition.x, clickPosition.y);
}



/* Quick Object */

void QuickBreak::click(sf::Vector2i cp)
{
	if (!clicking)
	{
		first_click = cp; clicking = true;
	}
}

sf::Vector2i QuickBreak::update(sf::Vector2i cp)
{
	if (clicking)
	{
		sf::Vector2i result = first_click - cp;
		first_click = cp;
		return result;
	}
	else return sf::Vector2i(0, 0);
}

sf::Vector2i QuickBreak::unclick(sf::Vector2i cp)
{
	sf::Vector2i result = update(cp);
	clicking = false;
	return result;
}