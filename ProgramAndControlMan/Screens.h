// @Author Michael Rainsford Ryan

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Globals.h"

const sf::Vector2f BUTTON_ONE_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 400.0f };
const sf::Vector2f BUTTON_TWO_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 520.0f };
const sf::Vector2f BUTTON_THREE_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 640.0f };

const int BUTTON_IMAGE_WIDTH{ 190 };
const int BUTTON_IMAGE_HEIGHT{ 49 };

const int BUTTON_WIDTH{ 342 };
const int BUTTON_HEIGHT{ 88 };

class Screens
{
	// Declare private data members
	sf::Texture m_backgroundTexture;
	sf::Texture m_buttonTexture;

	sf::Sprite m_backgroundSprite;
	sf::Sprite m_buttonSprite;

	sf::Font m_pacFont;

	sf::Text m_titleText;
	sf::Text m_buttonText;
	sf::Text m_helpText;
	sf::Text m_enterNameText;
	sf::Text m_nameText;

public:
	Screens();
	void loadFiles();
	void processEvents(sf::Event t_event, GameState & t_gameState, std::string & t_playerName, bool &t_gameOver);
	void menuEvents(sf::Event t_event, GameState & t_gameState, bool &t_gameOver);
	void nameScreenEvents(sf::Event t_event, GameState & t_gameState, std::string & t_playerName);
	void helpScreenEvents(sf::Event t_event, GameState & t_gameState);
	void draw(sf::RenderWindow & t_window, GameState t_gameState, std::string t_playerName);
};

