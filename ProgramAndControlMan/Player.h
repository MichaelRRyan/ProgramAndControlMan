/// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Cell.h"

class Player
{
	// Declare private data members
	sf::Texture m_spriteSheet;
	sf::Sprite m_body;
	sf::Vector2i m_pos;
	int m_score;

public:
	// Declare public function members
	Player();
	void loadFiles();

	void setPos(sf::Vector2i t_pos); // Set the row and column position of the player
	inline sf::Sprite getBody() { return m_body; }

	void move(Direction t_direction, Cell t_maze[][MAX_COLS]);
};

