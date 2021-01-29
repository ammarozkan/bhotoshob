#pragma once
#include <iostream>
#include <vector>
#include "Renderer.h"
#include "QuickSFML.h"
#include "Program.h"
#include <SFML/Graphics.hpp>

struct button_group
{
	std::vector<sf::Sprite> buttons;
	int getClickId(int x, int y);
	void addButton(sf::Image buttonImage);
	button_group();
};

struct button_group_id
{
	int button_group, button;
};

class Panel
{
private:

};



class QCore
{
private:
	Program program; QuickWindow editor;
	std::vector<sf::Sprite> sprites; int panelXPos = 600;
	std::vector<button_group> buttons; int selected_image = -1;
	std::vector<sf::Texture> textures;
public:
	QCore(sf::Vector2i size);

	button_group_id getClickId(int x,int y);

	void createNewButtonGroup();
	button_group* getButtonGroup(int id);

	void sync_imageSelection();

	void addSprite(sf::Sprite spr);

	/* Private For Editor */
	void calculate_selecteds();

	/* Using */

	void zoom();
	void save();
	void select_image(int img_id);
	void unselect_image();

	/* Image Effects */

	void unage_blur();
	void radiate_blur();
	void reverse_lights();
	void live_image();
	void remove_lights();
	void hand_draw(int limit);

	void Core();
	void Render();
	void DrawObjects();
	void DrawButtons();
	bool CoreController(sf::Event event);
};