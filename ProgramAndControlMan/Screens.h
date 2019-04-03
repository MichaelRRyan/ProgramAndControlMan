/// @Author Michael Rainsford Ryan
#ifndef SCREENS_H
#define SCREEENS_H

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
const sf::Vector2f BUTTON_BACK_POSITION{ static_cast<float>(BUTTON_IMAGE_WIDTH), static_cast<float>(WINDOW_HEIGHT - 60) };
const sf::Vector2f SCOREBOARD_POSITION{ static_cast<float>(WINDOW_WIDTH / 2 - 160), 170.0f };
const sf::Vector2f YOUR_SCORE_POSITION{ static_cast<float>(WINDOW_WIDTH / 2 - 160), 100.0f };

class Screens
{
	// Declare private data members
	sf::Texture m_backgroundTexture;
	sf::Texture m_buttonTexture;

	sf::Sprite m_backgroundSprite;
	sf::Sprite m_buttonSprite;
	sf::Sprite m_arrowSprite;

	sf::Font m_twosonFont;

	sf::Text m_titleText;
	sf::Text m_buttonText;
	sf::Text m_helpText;
	sf::Text m_enterNameText;
	sf::Text m_nameText;
	sf::Text m_pauseText;
	sf::Text m_endText;
	sf::Text m_scoreboardText;
	sf::Text m_yourScoreText;

	int m_characterNumber; // Player character number used for character selection
	bool m_gameOver; // Used to load the scoreboard file only once each time the player dies

	// Scoreboard
	std::string m_names[MAX_PLAYERS]; // Setup the name string array
	int m_scores[MAX_PLAYERS]; // Setup the scores array
	int m_characterNums[MAX_PLAYERS]; // Setup the character numbers array

public:
	Screens();
	void loadFiles();
	void setupText();
	void processEvents(sf::Event t_event, GameState & t_gameState, std::string & t_playerName, bool &t_gameOver, Player &t_player);
	void menuEvents(sf::Event t_event, GameState & t_gameState, bool &t_gameOver, std::string & t_playerName);
	void nameScreenEvents(sf::Event t_event, GameState & t_gameState, std::string & t_playerName);
	void backButtonEvents(sf::Event t_event, GameState & t_gameState);
	void characterScreenEvents(sf::Event t_event, GameState & t_gameState, Player &t_player);

	void draw(sf::RenderWindow & t_window, GameState t_gameState, std::string t_playerName, Player & t_player);
	void drawPauseScreen(sf::RenderWindow &t_window);
	void drawEndScreen(sf::RenderWindow &t_window, std::string t_playerName, int t_playerScore, int t_playerCharNum, Player t_player);

	void saveScoreToFile(std::string t_playerName, int t_playerScore, int t_playerCharNum);
	void readScore();
	void addScore(std::string t_playerName, int t_playerScore, int t_playerCharNum);
	void writeScore();
};

#endif // !SCREENS_H