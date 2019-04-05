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

	sf::RenderWindow m_window; // Render window
	bool m_exitGame; // Closes the window if true

	GameState m_gameState; // Current game state

	Cell m_maze[MAX_ROWS][MAX_COLS]; // Cell array to make the maze
	WalkerEnemy m_ghosts[MAX_GHOSTS]; // Enemies array
	Player m_player; // Player object
	Screens m_menuScreens; // Screens object
	
	sf::Font m_twosonFont; // Font for text objects

	sf::Text m_scoreText; // Text for player score
	sf::Text m_livesText; // Text for player lives

	sf::Texture m_terrainTexture; // Textures for the tiles
	sf::Texture m_hudIconsTexure; // Textures for the hud

	sf::Sprite m_tileSprite; // sprite for each tile
	sf::Sprite m_hudIcons; // Icons for the player's hud

	std::string m_playerName; // Players name string
};

#endif // !GAME

