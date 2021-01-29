#pragma once
#include <SFML/Graphics.hpp>
#include "Light.h"

struct Drawning
{
	sf::Image img; sf::Vector2i position, size;
	Drawning(sf::Sprite s);
	Drawning(sf::Image i, sf::Vector2i pos);
};

class Renderer
{
private:
	sf::Image image; sf::Sprite spr; sf::Texture texture;
public:
	Renderer(sf::Vector2i size);
	void background();
	sf::Image getImage();
	sf::Sprite getSprite();
	void updateSpr();

	/* Radiating */
	std::vector < sf::Vector2i > static getCollidedPixels(sf::Vector2i pixel,int rangeX, int rangeY);
	void static RadiatePixel(sf::Image &img,std::vector<sf::Vector2i> drawn,int size = 5, sf::Color color = sf::Color::Red,std::vector<sf::Vector2i> notDrawn = std::vector<sf::Vector2i>(),int counter = 0);

	/* Effects */
	sf::Image static unage_blur(sf::Image imgForBlue);
	sf::Image static radiate_blur(sf::Image imgForBlue);
	sf::Image static reverse_lights(sf::Image imgForBlue);
	sf::Image static live_image(sf::Image imgForBlue);
	sf::Image static remove_lights(sf::Image imgForBlue);
	sf::Image static hand_draw(sf::Image imgForBlue, int limit);

	void draw(sf::Image drawning, sf::Vector2i position);
	void draw(Drawning drawning);
	void draw(sf::Sprite spr);

	/* Drawning */
	void drawBox(int posX, int posY, Light light,sf::Color color);
};

