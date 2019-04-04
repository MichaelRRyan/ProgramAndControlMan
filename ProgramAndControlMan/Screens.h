/// @Author Michael Rainsford Ryan
#ifndef SCREENS_H
#define SCREENS_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Globals.h"
#include "Player.h"

const int BUTTON_IMAGE_WIDTH{ 190 };
const int BUTTON_IMAGE_HEIGHT{ 49 };

const int BUTTON_WIDTH{ 342 };
const int BUTTON_HEIGHT{ 88 };

const int HELP_SCREENS{ 3 };

const sf::Vector2f BUTTON_START_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 400.0f };
const sf::Vector2f BUTTON_HELP_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 510.0f };
const sf::Vector2f BUTTON_SCOREBOARD_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 620.0f };
const sf::Vector2f BUTTON_EXIT_POSITION{ static_cast<float>(WINDOW_WIDTH / 2), 730.0f };
const sf::Vector2f BUTTON_MENU_POSITION{ static_cast<float>(BUTTON_IMAGE_WIDTH), static_cast<float>(WINDOW_HEIGHT - 60) };
const sf::Vector2f BUTTON_NEXT_POSITION{ static_cast<float>(WINDOW_WIDTH - BUTTON_IMAGE_WIDTH), static_cast<float>(WINDOW_HEIGHT - 60) };
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

	sf::Text m_buttonText;
	sf::Text m_helpText;
	sf::Text m_enterNameText;
	sf::Text m_nameText;
	sf::Text m_pauseText;
	sf::Text m_endText;
	sf::Text m_scoreboardText;
	sf::Text m_yourScoreText;

	int m_characterNumber; // Player character number used for character selection
	int m_helpScreenNumber; // Number of the help screen the player is on
	bool m_scoreboardUpdated; // Used to load the scoreboard file only once each time the player dies

	// Scoreboard
	std::string m_names[MAX_PLAYERS]; // Setup the name string array
	int m_scores[MAX_PLAYERS]; // Setup the scores array
	int m_characterNums[MAX_PLAYERS]; // Setup the character numbers array

public:
	Screens();
	void loadFiles();
	void setupText();
	void setupHelpText(int t_screenNumber); // Sets up the health text to the screen number inputted

	void processEvents(sf::Event t_event, GameState &t_gameState, std::string & t_playerName, bool &t_gameOver, Player &t_player);
	void menuEvents(sf::Event t_event, GameState &t_gameState, bool &t_gameOver, std::string &t_playerName, Player &t_player);
	void nameScreenEvents(sf::Event t_event, GameState &t_gameState, std::string &t_playerName);
	void backButtonEvents(sf::Event t_event, GameState &t_gameState);
	void nextHelpEvents(sf::Event t_event); // Process events for the help menu next button
	void characterScreenEvents(sf::Event t_event, GameState &t_gameState, Player &t_player);

	void draw(sf::RenderWindow &t_window, GameState t_gameState, std::string t_playerName, Player &t_player);
	void drawPauseScreen(sf::RenderWindow &t_window);
	void drawEndScreen(sf::RenderWindow &t_window, std::string t_playerName, int t_playerScore, int t_playerCharNum, Player t_player);
	void drawScoreboard(sf::RenderWindow &t_window, Player t_player);
	void drawScoreboardScreen(sf::RenderWindow &t_window, Player t_player);

	void saveScoreToFile(std::string t_playerName, int t_playerScore, int t_playerCharNum);
	void readScore();
	void addScore(std::string t_playerName, int t_playerScore, int t_playerCharNum);
	void writeScore();
};

#endif // !SCREENS_H