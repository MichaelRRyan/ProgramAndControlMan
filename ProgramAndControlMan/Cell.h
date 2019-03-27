/// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Globals.h"

class Cell
{
	bool m_containsWall;
	bool m_containsCoin;
	sf::IntRect m_texturePosition;
	sf::Vector2f m_position;

public:
	// Declare public function members
	Cell();

	inline bool getContainsWall() { return m_containsWall; } // Returns whether or not the cell contains a wall
	inline bool getContainsCoin() { return m_containsCoin; } // Returns whether or not the cell contains a coin
	inline sf::IntRect getTexturePosition() { return m_texturePosition; } // Returns the texture rectangle of the cell
	//inline sf::Sprite getBody() { return body; } // Returns the sprite of the cell

	void setContainsWall(bool t_wall); // Sets the cell to have a wall or not
	void setContainsCoin(bool t_coin); // Sets the cell to have a coin or not
	inline void setPosition(sf::Vector2f t_position) { m_position = t_position; } // Sets the position of the cell
};

