#include "TextBox.h"
#include "QuickSFML.h"

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

TextBox::TextBox() : just_number(false)
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
	if (QuickFunctions::clickController(button,x,y))
	{
		string = ""; writing = true; return true;
		text.setString(string);
	}
	else return false;
}

bool TextBox::letter_write_controller(sf::Event e)
{
	if (writing && e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
	{
		writing = false;
	}
	else if (writing && e.type == sf::Event::TextEntered)
	{
		string += e.text.unicode;
		text.setString(string);
	}
	return (writing && e.type == sf::Event::TextEntered);
}

bool TextBox::number_write_controller(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed && writing)
	{
		if (e.key.code == sf::Keyboard::Num0) string += "0";
		else if (e.key.code == sf::Keyboard::Num1) string += "1";
		else if (e.key.code == sf::Keyboard::Num2) string += "2";
		else if (e.key.code == sf::Keyboard::Num3) string += "3";
		else if (e.key.code == sf::Keyboard::Num4) string += "4";
		else if (e.key.code == sf::Keyboard::Num5) string += "5";
		else if (e.key.code == sf::Keyboard::Num6) string += "6";
		else if (e.key.code == sf::Keyboard::Num7) string += "7";
		else if (e.key.code == sf::Keyboard::Num8) string += "8";
		else if (e.key.code == sf::Keyboard::Num9) string += "9";
		else if (e.key.code == sf::Keyboard::Numpad0) string += "0";
		else if (e.key.code == sf::Keyboard::Numpad1) string += "1";
		else if (e.key.code == sf::Keyboard::Numpad2) string += "2";
		else if (e.key.code == sf::Keyboard::Numpad3) string += "3";
		else if (e.key.code == sf::Keyboard::Numpad4) string += "4";
		else if (e.key.code == sf::Keyboard::Numpad5) string += "5";
		else if (e.key.code == sf::Keyboard::Numpad6) string += "6";
		else if (e.key.code == sf::Keyboard::Numpad7) string += "7";
		else if (e.key.code == sf::Keyboard::Numpad8) string += "8";
		else if (e.key.code == sf::Keyboard::Numpad9) string += "9";
		else if (e.key.code == sf::Keyboard::Enter) writing = false;
		text.setString(string);
		return true;
	}
	return false;
}

bool TextBox::write_controller(sf::Event e)
{
	if (just_number)
	{
		return number_write_controller(e);
	}
	else return letter_write_controller(e);
}

void TextBox::drawTextBox(sf::RenderWindow * window)
{
	window->draw(button);
	window->draw(text);
}

sf::String TextBox::getString() { return string; }

sf::Text TextBox::getText() { return text; }