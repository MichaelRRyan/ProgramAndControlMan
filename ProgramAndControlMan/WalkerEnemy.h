#pragma once

#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Cell.h"

class WalkerEnemy
{
	// Declare public data members
	sf::Texture m_spriteSheet;
	sf::Sprite m_body;
	sf::Vector2i m_pos;
	Direction m_moveDir;

public:
	WalkerEnemy();
	void loadFiles();

	inline sf::Sprite getBody() { return m_body; }

	void setPos(int t_row, int t_col);
	void move(Cell t_maze[][MAX_COLS]);
};
