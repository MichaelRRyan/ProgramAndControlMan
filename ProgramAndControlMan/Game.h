/// @Author Michael Rainsford Ryan
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Cell.h"
#include "Globals.h"
#include "Player.h"
#include "WalkerEnemy.h"
#include "Screens.h"

class Game
{
public:

	Game();
	~Game();

	void run();

private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void setupGame();
	void setupMaze();
	void setupFontAndText();
	void drawGameplay();

	sf::RenderWindow m_window;
	bool m_exitGame;

	GameState m_gameState;

	Cell m_maze[MAX_ROWS][MAX_COLS];
	WalkerEnemy m_ghosts[MAX_GHOSTS];
	Player m_player;
	Screens m_menuScreens;
	
	sf::Font m_twosonFont;

	sf::Text m_scoreText;
	sf::Text m_livesText;
	sf::Text m_gameOverText;

	sf::Texture m_terrainTexture;
	sf::Texture m_hudIconsTexure;

	sf::Sprite m_tileSprite;
	sf::Sprite m_hudIcons;

	std::string m_playerName;
};

#endif // !GAME

