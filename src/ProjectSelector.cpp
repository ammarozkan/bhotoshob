#include "ProjectSelector.h"
ProjectSelector::ProjectSelector(std::string font_path)
	: window(sf::VideoMode(400, 300), "Selector")
{
	font.loadFromFile(font_path); nameBox.init(200, 200, 100, 50, font);
	resolutionBox.init(0, 0, 100, 50, font,true);
	resolutionBox2.init(120, 0, 100, 50, font, true);

	result.render_size[0] = 1024; result.render_size[1] = 768;
	result.output_name = "output.png";
	result.first_input_img = "input.png";
}

void ProjectSelector::close()
{
	result.first_input_img = nameBox.getString().toAnsiString();
	result.render_size[0] = atoi(resolutionBox.getString().toAnsiString().c_str());
	result.render_size[1] = atoi(resolutionBox2.getString().toAnsiString().c_str());
	window.close();
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
	if (click_id == 0) close();
}

void ProjectSelector::events(sf::Event e)
{
	if (e.type == sf::Event::Closed) close();
	else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
	{
		if (nameBox.click_controller(e.mouseButton.x, e.mouseButton.y));
		else if (resolutionBox.click_controller(e.mouseButton.x, e.mouseButton.y));
		else if (resolutionBox2.click_controller(e.mouseButton.x, e.mouseButton.y));
		else click(e.mouseButton.x, e.mouseButton.y);
	}
	else if (nameBox.write_controller(e));
	else if (resolutionBox.write_controller(e));
	else if (resolutionBox2.write_controller(e));
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
		window.getWindow()->draw(input_text);
		nameBox.drawTextBox(window.getWindow());
		resolutionBox.drawTextBox(window.getWindow());
		resolutionBox2.drawTextBox(window.getWindow());
		window.display();
	}
	return result;
}