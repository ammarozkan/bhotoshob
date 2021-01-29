#include <iostream>
#include <vector>
#include "ProgramComplete.h"
#include "ProjectSelector.h"

int main(int argc, char* argv[])
{
	ProjectSelections spec;

	sf::Image button_image; button_image.create(100, 100, sf::Color::Blue);
	for (int x = 0; x < 100; x++) for (int y = 0; y < 5; y++) button_image.setPixel(x, y, sf::Color::Black);
	sf::Texture button_texture; button_texture.loadFromImage(button_image);

	if (argc > 1)
	{
		sf::Texture ct; ct.loadFromFile(argv[1]);
		spec.first_input_img = argv[1];
		spec.render_size[0] = ct.getSize().x; spec.render_size[1] = ct.getSize().y;
	}
	else
	{
		ProjectSelector selector("bebasneue.ttf");
		sf::Sprite selector_button(button_texture);
		selector_button.setScale(1, 0.5);
		selector_button.setPosition(300, 250);
		selector.addButton(selector_button);

		spec = selector.core();
	}

	std::cout << spec.first_input_img << " inputet " << spec.render_size[0] << " " << spec.render_size[1] << std::endl;

	QCore core({ spec.render_size[0],spec.render_size[1] });
	core.createNewButtonGroup();
	if (core.getButtonGroup(1) != nullptr)
	{
		sf::Sprite load_texture_button(button_texture);
		for (int i = 0; i < 8; i++)
		{
			load_texture_button.setPosition(700, 100 * i);
			core.getButtonGroup(1)->buttons.push_back(load_texture_button);
		}
	}

	sf::Texture test_texture; 
	if (!test_texture.loadFromFile(spec.first_input_img)) return -1;
	sf::Sprite spriteTest(test_texture);
	spriteTest.setPosition(0, 0);

	core.addSprite(spriteTest);

	core.Core();

	return 0;
}