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
	std::vector<sf::Sprite> buttons; sf::Text resolution_text,resolution_text2; int rc[2] = { 0,0 }; bool tX, tY, tName;
	sf::String input = ""; TextBox nameBox;
public:
	ProjectSelector(std::string font_path);

	void addButton(sf::Sprite button);

	void draw_buttons();
	void events(sf::Event e);

	void click(int x, int y);
	int get_clicked_button_id(int x, int y);
	ProjectSelections core();


	void change_resolution(int res);

	void update_visuals();
};

