/// @Author Michael Rainsford Ryan

#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Globals.h"
#include "Player.h"

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
	void drawMaze();

	sf::RenderWindow m_window;
	bool m_exitGame;

	Cell m_maze[MAX_ROWS][MAX_COLS];
	Player m_player;
};

#endif // !GAME

