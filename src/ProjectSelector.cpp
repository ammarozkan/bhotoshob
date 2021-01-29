#include "ProjectSelector.h"
ProjectSelector::ProjectSelector(std::string font_path)
	: window(sf::VideoMode(400, 300), "Selector")
{
	font.loadFromFile(font_path); nameBox.init(200, 200, 100, 50, font);

	result.render_size[0] = 1024; result.render_size[1] = 768;
	result.output_name = "output.png";
	result.first_input_img = "input.png";

	resolution_text.setString(std::to_string(result.render_size[0]));

	resolution_text.setFont(font);
	resolution_text.setPosition(0, 0);
	resolution_text.setCharacterSize(30);
	resolution_text2.setFont(font);
	resolution_text2.setPosition(100, 0);
	resolution_text2.setCharacterSize(30);
	update_visuals();

}

void ProjectSelector::addButton(sf::Sprite button)
{
	buttons.push_back(button);
}


void ProjectSelector::draw_buttons()
{
	for (int i = 0; i < buttons.size(); i++) window.draw(buttons[i]);
}
int ProjectSelector::get_clicked_button_id(int x, int y)
{
	for (int i = 0;i< buttons.size();i++)
	{
		bool xControl = buttons[i].getPosition().x <= x && buttons[i].getPosition().x + (buttons[i].getScale().x * buttons[i].getTexture()->getSize().x) >= x;
		bool yControl = buttons[i].getPosition().y <= y && buttons[i].getPosition().y + (buttons[i].getScale().y * buttons[i].getTexture()->getSize().y) >= y;
		if (xControl && yControl) return i;
	}
	return -1;
}

void ProjectSelector::click(int x, int y)
{
	int click_id = get_clicked_button_id(x, y);
	if (click_id == 0) window.close();
	else if (click_id == 1) { tX = true; tY = false; tName = false; resolution_text.setString(""); }
	else if (click_id == 2) { tX = false; tY = true; tName = false; resolution_text2.setString(""); }
	else if (click_id == 3) { tX = false; tY = false; tName = true; }
}

void ProjectSelector :: update_visuals()
{
	resolution_text.setString(std::to_string(result.render_size[0]));
	resolution_text2.setString(std::to_string(result.render_size[1]));
}


void ProjectSelector::change_resolution(int res)
{
	if (rc[res] > 2) rc[res] = 0;

	if (rc[res] == 0) result.render_size[res] = 1280;
	else if (rc[res] == 1) result.render_size[res] = 720;
	else if (rc[res] == 2) result.render_size[res] = 600;
	rc[res]++;
	update_visuals();
}

void ProjectSelector::events(sf::Event e)
{
	if (e.type == sf::Event::Closed)
	{
		result.first_input_img = nameBox.getString().toAnsiString();
		window.close();
	}
	else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
	{
		if (nameBox.click_controller(e.mouseButton.x, e.mouseButton.y));
		else click(e.mouseButton.x, e.mouseButton.y);
	}
	else if (nameBox.write_controller(e));
	else if (e.type == sf::Event::KeyPressed)
	{
		if (tX)
		{
			if (e.key.code == sf::Keyboard::Num0) input += "0";
			else if (e.key.code == sf::Keyboard::Num1) input += "1";
			else if (e.key.code == sf::Keyboard::Num2) input += "2";
			else if (e.key.code == sf::Keyboard::Num3) input += "3";
			else if (e.key.code == sf::Keyboard::Num4) input += "4";
			else if (e.key.code == sf::Keyboard::Num5) input += "5";
			else if (e.key.code == sf::Keyboard::Num6) input += "6";
			else if (e.key.code == sf::Keyboard::Num7) input += "7";
			else if (e.key.code == sf::Keyboard::Num8) input += "8";
			else if (e.key.code == sf::Keyboard::Num9) input += "9";
			else if (e.key.code == sf::Keyboard::Enter)
			{
				result.render_size[0] = atoi(input.toAnsiString().c_str());
				input = ""; tX = false;
				update_visuals();
			}
		}
		else if (tY)
		{
			if (e.key.code == sf::Keyboard::Num0) input += "0";
			else if (e.key.code == sf::Keyboard::Num1) input += "1";
			else if (e.key.code == sf::Keyboard::Num2) input += "2";
			else if (e.key.code == sf::Keyboard::Num3) input += "3";
			else if (e.key.code == sf::Keyboard::Num4) input += "4";
			else if (e.key.code == sf::Keyboard::Num5) input += "5";
			else if (e.key.code == sf::Keyboard::Num6) input += "6";
			else if (e.key.code == sf::Keyboard::Num7) input += "7";
			else if (e.key.code == sf::Keyboard::Num8) input += "8";
			else if (e.key.code == sf::Keyboard::Num9) input += "9";
			else if (e.key.code == sf::Keyboard::Enter)
			{
				result.render_size[1] = atoi(input.toAnsiString().c_str());
				input = ""; tY = false;
				update_visuals();
			}
		}
	}

	if (e.type == sf::Event::TextEntered)
	{
		if (tName)
		{
			if (e.key.code == sf::Keyboard::Enter)
			{
				result.first_input_img = input;
				input = ""; tName = false;
				update_visuals();
			}
			else input += e.text.unicode;
		}
	}
}

ProjectSelections ProjectSelector::core()
{
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			events(e);
		}

		sf::Text input_text(input, font), first_input(result.first_input_img,font);
		input_text.setPosition(100, 100);
		first_input.setPosition(200, 0);


		window.clear();
		draw_buttons();
		window.getWindow()->draw(resolution_text);
		window.getWindow()->draw(resolution_text2);
		window.getWindow()->draw(input_text);
		nameBox.drawTextBox(window.getWindow());
		window.display();

	}
	return result;
}