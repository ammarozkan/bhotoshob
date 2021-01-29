#pragma once
#include "QuickSFML.h"
#include "Renderer.h"
#include <vector>

class Program
{
private:
	QuickWindow window; Renderer render_machine; std::vector<Drawning> objects;
public:
	Program(sf::Vector2i size);
	void render(std::vector<sf::Sprite> drawnings = std::vector<sf::Sprite>());
	void addSprite(sf::Sprite spr);
	void addDrawning(Drawning drw);
	void controlEvents();
	void clear();
	void setZoom(int zoom);
	int getZoom();

	Renderer getRender_machine();
};