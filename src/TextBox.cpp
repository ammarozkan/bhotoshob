#include "TextBox.h"

void TextBox::init(int x, int y, int sizeX, int sizeY, sf::Font f, bool jn)
{
	font = f;
	text.setString("");
	text.setFont(font);
	text.setCharacterSize(30);
	just_number = jn;
	button.setPosition(x, y);
	text.setPosition(x, y);
	text.setCharacterSize(30);
	sf::Image img; img.create(sizeX, sizeY, sf::Color::Blue);
	text_box_texture.loadFromImage(img);
	button.setTexture(text_box_texture);
}

TextBox::TextBox()
{

}

TextBox::TextBox(int x, int y, int sizeX, int sizeY, sf::Font f , bool jn)
	: font(f),text("",font,30U), just_number(jn)
{
	button.setPosition(x, y);
	text.setPosition(x, y);
	text.setCharacterSize(30);
	sf::Image img; img.create(sizeX, sizeY,sf::Color::Blue);
	text_box_texture.loadFromImage(img);
	button.setTexture(text_box_texture);
}


bool TextBox::click_controller(int x, int y)
{
	bool controlX = button.getPosition().x <= x && button.getPosition().x + (button.getScale().x * button.getTexture()->getSize().x);
	bool controlY = button.getPosition().y <= y && button.getPosition().y + (button.getScale().y * button.getTexture()->getSize().y);
	if (controlX && controlY)
	{
		string = ""; writing = true; return true;
		text.setString(string);
	}
	else return false;
}

bool TextBox::write_controller(sf::Event e)
{
	if (writing && e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
	{
		writing = false;
		return true;
	}
	else if (writing && e.type == sf::Event::TextEntered)
	{
		string += e.text.unicode;
		text.setString(string);
		return true;
	}
	else return false;
}

void TextBox::drawTextBox(sf::RenderWindow * window)
{
	window->draw(button);
	window->draw(text);
}

sf::String TextBox::getString() { return string; }

sf::Text TextBox::getText() { return text; }