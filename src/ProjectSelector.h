#pragma once
#include "QuickSFML.h"
#include "TextBox.h"

struct ProjectSelections
{
	int render_size[2]; std::string output_name, first_input_img;
};

class ProjectSelector
{
private:
	QuickWindow window; ProjectSelections result; sf::Font font;
	std::vector<sf::Sprite> buttons; int rc[2] = { 0,0 };
	sf::String input = ""; TextBox nameBox,resolutionBox,resolutionBox2;

	void close();
public:
	ProjectSelector(std::string font_path);

	void addButton(sf::Sprite button);

	void draw_buttons();
	void events(sf::Event e);

	void click(int x, int y);
	int get_clicked_button_id(int x, int y);
	ProjectSelections core();
};

