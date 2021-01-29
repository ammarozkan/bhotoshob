#pragma once
#include <SFML/Graphics.hpp>
class TextBox
{
private:
	bool writing = false; sf::String string; sf::Sprite button; sf::Text text; sf::Font font; bool just_number;
	sf::Texture text_box_texture;

	/* Only number function */
	bool number_write_controller(sf::Event e);
	/* Normal function */
	bool letter_write_controller(sf::Event e);
public:
	/* Init function for after defining */
	void init(int x, int y, int sizeX, int sizeY, sf::Font font, bool just_number = false);
	/* Defining functions */
	TextBox(int x, int y,int sizeX, int sizeY, sf::Font font, bool just_number = false); TextBox();

	/* Is clicked to textbox? */
	bool click_controller(int x, int y); 
	/* Writing controller function. */
	bool write_controller(sf::Event event); 
	/* QuickDraw */
	void drawTextBox(sf::RenderWindow* window);

	sf::String getString();
	sf::Text getText();
};

