#include <iostream>
#include "Renderer.h"

sf::Color p(sf::Color a, int b)
{
	return sf::Color(a.r / b, a.g / b, a.b / b);
}

sf::Color operator/(sf::Color a, int b)
{
	return sf::Color(a.r / b, a.g / b, a.b / b);
}

sf::Color operator*(sf::Color a, float b)
{
	return sf::Color(a.r * b>255?255: a.r * b
		, a.g * b>255?255: a.g * b
		, a.b * b>255?255: a.b * b);
}

Renderer::Renderer(sf::Vector2i size)
{
	image.create(size.x, size.y, sf::Color::Black);
}

void Renderer::background()
{
	for (int i = 0; i < image.getSize().x; i++) for (int j = 0; j < image.getSize().y; j++) image.setPixel(i, j, sf::Color(100, 100, 0.25 * i, 255));
}

sf::Image Renderer::getImage() { return image; }

std::vector<sf::Vector2i> Renderer::getCollidedPixels(sf::Vector2i pixel, int rx, int ry)
{
	std::vector<sf::Vector2i> vec;
	for (int x = -1; x < 2; x++) for (int y = -1; y < 2; y++)
	{
		if (pixel.x + x < 0 || pixel.x + x > rx || pixel.y + y < 0 || pixel.y + y > ry) continue;
		else vec.push_back(sf::Vector2i(pixel.x+x, pixel.y+y));
		if (vec.size() > 8) break;
	}
	return vec;
}

sf::Sprite Renderer::getSprite()
{
	return spr;
}

void Renderer::RadiatePixel(sf::Image& img, std::vector<sf::Vector2i> drawn,int size, sf::Color color, std::vector<sf::Vector2i> notDrawn, int counter)
{
	if (counter > size) return;
	std::vector<sf::Vector2i> t;
	t.insert(t.end(), drawn.begin(), drawn.end());
	t.insert(t.end(), notDrawn.begin(), notDrawn.end());
	/* Filter State */
	for (sf::Vector2i pixel : drawn)
	{
		bool isSuc = true;
		for (sf::Vector2i notPixel : notDrawn) if (notPixel == pixel) isSuc = false;
		if (isSuc)
		{
			img.setPixel(pixel.x, pixel.y, color);
			std::cout << "Working work " << counter + 1 << std::endl;
			RadiatePixel(img, getCollidedPixels(pixel, 10, 10), size, sf::Color(color.r / 2, color.b / 2, color.g / 2), t, counter + 1);
		}
	}
}

/* Effects */


sf::Image Renderer::unage_blur(sf::Image img)
{
	for (int x = 1; x < img.getSize().x; x++) for (int y = 1; y < img.getSize().y; y++)
	{
		img.setPixel(x - 1, y, p(img.getPixel(x, y) + img.getPixel(x, y),2));
	}
	return img;
}

sf::Image Renderer::radiate_blur(sf::Image imgForBlue)
{
	for (int x = 0; x < imgForBlue.getSize().x; x++) for (int y = 0; y < imgForBlue.getSize().y; y++)
	{
		sf::Color color = imgForBlue.getPixel(x, y);
		std::vector<sf::Vector2i> collided_pixels = getCollidedPixels(sf::Vector2i(x, y), imgForBlue.getSize().x, imgForBlue.getSize().y);
		for (sf::Vector2i px : collided_pixels)
		{
			if (px.x<0 || px.x>=imgForBlue.getSize().x || px.y<0 || px.y>=imgForBlue.getSize().y) continue;
			else imgForBlue.setPixel(px.x, px.y, p(imgForBlue.getPixel(px.x, px.y) + color, 2));
		}
	}
	return imgForBlue;
}

sf::Image Renderer::reverse_lights(sf::Image imgForBlue)
{
	for (int x = 0; x < imgForBlue.getSize().x; x++) for (int y = 0; y < imgForBlue.getSize().y; y++)
	{
		sf::Color color = imgForBlue.getPixel(x, y);
		if (color.r > 150 && color.g > 150 && color.b > 150)
		{
			imgForBlue.setPixel(x, y, sf::Color(255 - color.r, 255 - color.g, 255 - color.b));
		}
		else if (color.r > 100 && color.g > 100 && color.b > 100)
		{
			imgForBlue.setPixel(x, y, sf::Color(100 + color.r, color.g, color.b));
		}
	}
	return imgForBlue;
}

sf::Image Renderer::live_image(sf::Image imgForBlue)
{
	for (int x = 0; x < imgForBlue.getSize().x; x++) for (int y = 0; y < imgForBlue.getSize().y; y++)
	{
		sf::Color c = imgForBlue.getPixel(x, y);
		imgForBlue.setPixel(x, y, sf::Color(c.r * 1.01, c.g, c.b));
	}
	return imgForBlue;
}

sf::Image Renderer::remove_lights(sf::Image imgForBlue)
{
	for (int x = 0; x < imgForBlue.getSize().x; x++) for (int y = 0; y < imgForBlue.getSize().y; y++)
	{
		sf::Color c = imgForBlue.getPixel(x, y);
		imgForBlue.setPixel(x, y, sf::Color(c.r > 150 ? 100 : c.r, c.g > 150 ? 100 : c.g, c.b > 150 ? 100 : c.b));
	}
	return imgForBlue;
}

sf::Image Renderer::hand_draw(sf::Image imgForBlue, int limit)
{
	for (int x = 0; x < imgForBlue.getSize().x; x++) for (int y = 0; y < imgForBlue.getSize().y; y++)
	{
		sf::Color c = imgForBlue.getPixel(x, y);
		if (c.r > limit && c.g > limit && c.b > limit)
		{
			imgForBlue.setPixel(x, y, c*1.3);
		}
		else imgForBlue.setPixel(x, y, c/5);
	}
	return imgForBlue;
}



void Renderer::draw(sf::Image img, sf::Vector2i position)
{
	std::cout << "Drawning " << img.getSize().x << " " << img.getSize().y << std::endl;
	for (int x = 0; x < img.getSize().x && x+position.x < (int)image.getSize().x; x++)
	{
		if (x+position.x < 0) continue;
		else for (int y = 0; y < img.getSize().y  && y +position.y < (int)image.getSize().y ; y++)
		{
			if (y+ position.y < 0)continue;
			else image.setPixel(x + position.x, y + position.y, img.getPixel(x, y));
		}
	}
}

void Renderer::draw(Drawning drawning)
{
	draw(drawning.img, drawning.position);
}

void Renderer::draw(sf::Sprite spr)
{
	sf::Image img = spr.getTexture()->copyToImage();
	draw(img, sf::Vector2i(spr.getPosition().x, spr.getPosition().y));
}

void Renderer::updateSpr()
{
	texture.loadFromImage(image);
	spr.setTexture(texture);
}