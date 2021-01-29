#include "ProgramComplete.h"

button_group::button_group()
{

}

int button_group::getClickId(int x, int y)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		bool xControl = x > buttons[i].getPosition().x && x < buttons[i].getPosition().x + (buttons[i].getScale().x * buttons[i].getTexture()->getSize().x);
		bool yControl = y > buttons[i].getPosition().y && y < buttons[i].getPosition().y + (buttons[i].getScale().y * buttons[i].getTexture()->getSize().y);
		if (xControl&&yControl)
		{
			return i;
		}
	}
	return -1;
}

void button_group::addButton(sf::Image img)
{
	sf::Texture txtr; txtr.loadFromImage(img);
	buttons.push_back(sf::Sprite(txtr));
}


QCore::QCore(sf::Vector2i size)
	: program(size),editor(sf::VideoMode(800,600),"Abode Photoshop Lite")
{
	program.setZoom(1);
	editor.setZoom(1);
	createNewButtonGroup();
}


void QCore::addSprite(sf::Sprite spr)
{
	sprites.push_back(spr);
	spr.setScale(100/(float)spr.getTexture()->getSize().x, 100/ (float)spr.getTexture()->getSize().y);
	spr.setPosition(panelXPos, (sprites.size() - 1) * 100);
	buttons[0].buttons.push_back(spr);
}




void QCore::sync_imageSelection()
{
	buttons[0].buttons = std::vector<sf::Sprite>();
	int i = 0;
	for (sf::Sprite copy : sprites)
	{
		copy.setPosition(panelXPos, i * 100);
		sf::Vector2f wh(copy.getTexture()->getSize().x, copy.getTexture()->getSize().y);
		copy.setScale(100 / wh.x, 100 / wh.y);
		buttons[0].buttons.push_back(copy);
		std::cout << "Syn " << i << std::endl;
		i++;
	}
}

void QCore::Render()
{
	program.render(sprites);
}

void QCore::DrawObjects()
{
	for (sf::Sprite drawning_sprite : sprites)
	{
		editor.draw(drawning_sprite);
	}
}

void QCore::DrawButtons()
{
	for (button_group bg : buttons) for (sf::Sprite button_sprite : bg.buttons) editor.draw(button_sprite, true);
}


button_group_id QCore::getClickId(int x, int y)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		int id = buttons[i].getClickId(x, y);
		if (id != -1) return { i,id };
	}
	return { -1,-1 };
}

void QCore::calculate_selecteds()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		if (i == selected_image)
		{
			//sprites[i].setColor(sf::Color::Blue);
			buttons[0].buttons[i].setColor(sf::Color::Blue);
		}
		else
		{
			buttons[0].buttons[i].setColor(sf::Color::White);
			//sprites[i].setColor(sf::Color::White);
		}
	}
}

/* For Using */

void QCore::zoom()
{
	int zoom = editor.getZoom();
	zoom++;
	if (zoom > 5) zoom = 1;
	editor.setZoom(zoom);
}

void QCore::save()
{
	program.render(sprites);
	program.getRender_machine().getImage().saveToFile("output.png");
}

/* Effects */

void QCore::unage_blur()
{
	if (selected_image == -1) std::cout << "Not selected for blur..." << std::endl;
	else
	{
		std::cout << "Unage bluring selected image: " << selected_image << std::endl;
		sf::Image blured = Renderer::unage_blur(sprites[selected_image].getTexture()->copyToImage());
		sf::Texture blured_texture; blured_texture.loadFromImage(blured);
		textures.push_back(blured_texture);
		sprites[selected_image].setTexture(textures[textures.size() - 1]);
		std::cout << "Unage blurred image " << selected_image << std::endl;
	}
}


void QCore::radiate_blur()
{
	if (selected_image == -1) std::cout << "Not selected for blur..." << std::endl;
	else
	{
		std::cout << "Radiate bluring selected image: " << selected_image << std::endl;
		sf::Image blured = Renderer::radiate_blur(sprites[selected_image].getTexture()->copyToImage());
		sf::Texture blured_texture; blured_texture.loadFromImage(blured);
		textures.push_back(blured_texture);
		sprites[selected_image].setTexture(textures[textures.size() - 1]);
		std::cout << "Radiate blurred image " << selected_image << std::endl;
	}
}

void QCore::reverse_lights()
{
	if (selected_image == -1) std::cout << "Not selected for reverse lights..." << std::endl;
	else
	{
		std::cout << "Reversing lights selected image: " << selected_image << std::endl;
		sf::Image blured = Renderer::reverse_lights(sprites[selected_image].getTexture()->copyToImage());
		sf::Texture blured_texture; blured_texture.loadFromImage(blured);
		textures.push_back(blured_texture);
		sprites[selected_image].setTexture(textures[textures.size() - 1]);
		std::cout << "Reversed lights image " << selected_image << std::endl;
	}
}

void QCore::live_image()
{
	if (selected_image == -1) std::cout << "Not selected for live image..." << std::endl;
	else
	{
		std::cout << "Living selected image: " << selected_image << std::endl;
		sf::Image blured = Renderer::live_image(sprites[selected_image].getTexture()->copyToImage());
		sf::Texture blured_texture; blured_texture.loadFromImage(blured);
		textures.push_back(blured_texture);
		sprites[selected_image].setTexture(textures[textures.size() - 1]);
		std::cout << "Lived image " << selected_image << std::endl;
	}
}

void QCore::remove_lights()
{
	if (selected_image == -1) std::cout << "Not selected for killing lights..." << std::endl;
	else
	{
		std::cout << "killing lights selected image: " << selected_image << std::endl;
		sf::Image blured = Renderer::remove_lights(sprites[selected_image].getTexture()->copyToImage());
		sf::Texture blured_texture; blured_texture.loadFromImage(blured);
		textures.push_back(blured_texture);
		sprites[selected_image].setTexture(textures[textures.size() - 1]);
		std::cout << "Killed lights image " << selected_image << std::endl;
	}
}

void QCore::hand_draw(int limit)
{
	if (selected_image == -1) std::cout << "Not selected for hand draw..." << std::endl;
	else
	{
		std::cout << "Hand draw selected image: " << selected_image << std::endl;
		sf::Image blured = Renderer::hand_draw(sprites[selected_image].getTexture()->copyToImage(),limit);
		sf::Texture blured_texture; blured_texture.loadFromImage(blured);
		textures.push_back(blured_texture);
		sprites[selected_image].setTexture(textures[textures.size() - 1]);
		std::cout << "Hand drawed image " << selected_image << std::endl;
	}
}

/* Useful funcs */

void QCore::select_image(int img_id)
{
	selected_image = img_id;
	calculate_selecteds();
}

void QCore::unselect_image()
{
	selected_image = -1;
	calculate_selecteds();
}

bool QCore::CoreController(sf::Event event)
{
	if (event.type == sf::Event::Closed)
	{
		editor.close();
		return true;
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.x > panelXPos)
		{
			button_group_id id = getClickId(event.mouseButton.x, event.mouseButton.y);
			if (id.button_group == 0) select_image(id.button);
			else if (id.button_group == 1)
			{
				if (id.button == 0) unage_blur();
				else if (id.button == 1) reverse_lights();
				else if (id.button == 2) live_image();
				else if (id.button == 3) unselect_image();
				else if (id.button == 4) hand_draw(75);
				else if (id.button == 5) program.render(sprites);
			}
			else if (id.button_group != -1 && id.button != -1) std::cout << "Clicked:" << id.button_group << " " << id.button << std::endl;
		}
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::W) sync_imageSelection();
		else if (event.key.code == sf::Keyboard::Z) zoom();
		else if (event.key.code == sf::Keyboard::R) program.render(sprites);
		else if (event.key.code == sf::Keyboard::B) unage_blur();
		else if (event.key.code == sf::Keyboard::N) radiate_blur();
		else if (event.key.code == sf::Keyboard::E) reverse_lights();
		else if (event.key.code == sf::Keyboard::L) live_image();
		else if (event.key.code == sf::Keyboard::H) remove_lights();
		else if (event.key.code == sf::Keyboard::U) unselect_image();
		else if (event.key.code == sf::Keyboard::M) hand_draw(75);
		else if (event.key.code == sf::Keyboard::S) save();
	}
	else return false;
}

void QCore::Core()
{
	while (editor.isOpen())
	{
		sf::Event event;
		while (editor.pollEvent(event))
		{
			if(CoreController(event));
		}
		editor.clear();
		DrawObjects();
		DrawButtons();
		editor.display();
	}
}


void QCore::createNewButtonGroup()
{
	buttons.push_back(button_group());
}

button_group* QCore::getButtonGroup(int id)
{
	if (id >= buttons.size())
	{
		std::cout << "Buttons dont have " << id << " group" << std::endl;
		return nullptr;
	}
	else
	{
		return &buttons[id];
	}
}