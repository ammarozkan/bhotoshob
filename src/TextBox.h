#pragma once
#include <SFML/Graphics.hpp>
class TextBox
{
private:
	bool writing = false; sf::String string; sf::Sprite button; sf::Text text; sf::Font font; bool just_number;
	sf::Texture text_box_texture;
public:
	void init(int x, int y, int sizeX, int sizeY, sf::Font font, bool just_number = false);
	TextBox(int x, int y,int sizeX, int sizeY, sf::Font font, bool just_number = false);
	TextBox();

	bool click_controller(int x, int y);

	bool write_controller(sf::Event event);

	void drawTextBox(sf::RenderWindow* window);

	sf::String getString();
	sf::Text getText();
};

