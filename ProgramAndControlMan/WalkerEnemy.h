#pragma once

#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Cell.h"

class WalkerEnemy
{
	// Declare private data members
	const int MOVEMENT_TIME = 10;

	sf::Texture m_spriteSheet;
	sf::Sprite m_body;
	sf::Vector2i m_pos;
	sf::Vector2i m_previousPos; // Used for animation
	Direction m_moveDir;
	int m_moveTimer;

	// Texture variables
	sf::Vector2i m_characterNumber;
	int m_characterHeight;
	int m_characterWidthMargin;
	int m_characterDirection;

public:
	WalkerEnemy();
	void loadFiles();

	inline sf::Sprite getBody() { return m_body; }
	inline sf::Vector2i getPos() { return m_pos; } // Return the row and col position of the ghost

	inline void setMoveTimer(int t_moveDelay) { m_moveTimer = t_moveDelay; } // Set the delay between movements
	void setPos(int t_row, int t_col);

	void move(Cell t_maze[][MAX_COLS], WalkerEnemy t_ghosts[]);
	void setTextureDirection(); // Set the correct texture for the direction the enemy is facing
};

