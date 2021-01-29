#include "Program.h"

Drawning::Drawning(sf::Sprite s)
{
	img = s.getTexture()->copyToImage();
	position = sf::Vector2i(s.getPosition().x, s.getPosition().y);
	size = sf::Vector2i(s.getScale().x, s.getScale().y);
}

Drawning::Drawning(sf::Image i, sf::Vector2i pos)
{
	img = i; position = pos;
}

Program::Program(sf::Vector2i size)
	: window(sf::VideoMode(size.x,size.y),"Photor Extreme Renderer Machine Lite Edition Free Mega Ultra 50000x"), render_machine(size)
{
	
}

void Program::render(std::vector<sf::Sprite> drawnings)
{
	window.clear();
	render_machine.background();
	for (int i = 0; i < drawnings.size(); i++) 
		render_machine.draw(drawnings[i]);
	for (int i = 0; i < objects.size(); i++) 
		render_machine.draw(objects[i]);
	render_machine.updateSpr();
	window.draw(render_machine.getImage());
	window.display();
}

void Program::addSprite(sf::Sprite add)
{
	objects.push_back(Drawning(add));
}

void Program::addDrawning(Drawning drwn)
{
	objects.push_back(Drawning(drwn));
}

void Program::controlEvents()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		if(e.type == sf::Event::Closed) window.close();
	}
}

void Program::clear()
{
	objects = std::vector<Drawning>();
}

Renderer Program::getRender_machine()
{
	return render_machine;
}


void Program::setZoom(int zoom)
{
	window.setZoom(zoom);
}

int Program::getZoom()
{
	return window.getZoom();
}