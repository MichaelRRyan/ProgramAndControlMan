/// @Author Michael Rainsford Ryan

#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Globals.h"
#include "Player.h"
#include "WalkerEnemy.h"
#include "Screens.h"

const unsigned MAX_GHOSTS{ 4 };

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
	void drawMaze();
	Direction checkMovementInput(sf::Event t_nextEvent);

	sf::RenderWindow m_window;
	bool m_exitGame;
	bool m_gameOver;

	Cell m_maze[MAX_ROWS][MAX_COLS];
	WalkerEnemy m_ghost[MAX_GHOSTS];
	Player m_player;
	Screens m_menuScreens;
	

	sf::Font m_arialFont;
	sf::Text m_scoreText;
	sf::Text m_gameOverText;
};

#endif // !GAME

