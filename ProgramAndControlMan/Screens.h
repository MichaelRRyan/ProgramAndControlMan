// @Author Michael Rainsford Ryan

#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"

const sf::Vector2f BUTTON_ONE_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 200.0f };
const sf::Vector2f BUTTON_TWO_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 400.0f };
const sf::Vector2f BUTTON_THREE_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 600.0f };

class Screens
{
	// Declare private data members
	sf::Texture m_backgroundTexture;
	sf::Texture m_buttonTexture;

	sf::Sprite m_backgroundSprite;
	sf::Sprite m_buttonSprite;

	sf::Font m_arialFont;

	sf::Text m_titleText;
	sf::Text m_buttonText;
	sf::Text m_helpText;

public:
	Screens();
	void loadFiles();
	void processEvents(sf::Event t_event);
	void draw(sf::RenderWindow t_window);
};

