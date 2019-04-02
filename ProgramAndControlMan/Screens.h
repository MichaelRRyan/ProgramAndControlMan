// @Author Michael Rainsford Ryan

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Globals.h"
#include "Player.h"

const int BUTTON_IMAGE_WIDTH{ 190 };
const int BUTTON_IMAGE_HEIGHT{ 49 };

const int BUTTON_WIDTH{ 342 };
const int BUTTON_HEIGHT{ 88 };

const sf::Vector2f BUTTON_ONE_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 400.0f };
const sf::Vector2f BUTTON_TWO_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 520.0f };
const sf::Vector2f BUTTON_THREE_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 640.0f };
const sf::Vector2f BUTTON_HELP_POSITION{ static_cast<float>(BUTTON_IMAGE_WIDTH), static_cast<float>(WINDOW_HEIGHT - 60) };

class Screens
{
	// Declare private data members
	sf::Texture m_backgroundTexture;
	sf::Texture m_buttonTexture;

	sf::Sprite m_backgroundSprite;
	sf::Sprite m_buttonSprite;
	sf::Sprite m_arrowSprite;

	sf::Font m_pacFont;

	sf::Text m_titleText;
	sf::Text m_buttonText;
	sf::Text m_helpText;
	sf::Text m_enterNameText;
	sf::Text m_nameText;

	int m_characterNumber;

	// Scoreboard
	std::string m_names[MAX_PLAYERS]; // Setup the name string array
	int m_scores[MAX_PLAYERS]; // Setup the scores array
	int m_characterNums[MAX_PLAYERS]; // Setup the character numbers array

public:
	Screens();
	void loadFiles();
	void setupText();
	void processEvents(sf::Event t_event, GameState & t_gameState, std::string & t_playerName, bool &t_gameOver, Player &t_player);
	void menuEvents(sf::Event t_event, GameState & t_gameState, bool &t_gameOver);
	void nameScreenEvents(sf::Event t_event, GameState & t_gameState, std::string & t_playerName);
	void helpScreenEvents(sf::Event t_event, GameState & t_gameState);
	void characterScreenEvents(sf::Event t_event, GameState & t_gameState, Player &t_player);
	void draw(sf::RenderWindow & t_window, GameState t_gameState, std::string t_playerName, Player & t_player);

	void saveScoreToFile(std::string t_playerName, int t_playerScore, int t_playerCharNum);
	void readScore();
	void addScore(std::string t_playerName, int t_playerScore, int t_playerCharNum);
	void writeScore();
};

