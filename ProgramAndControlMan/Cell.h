/// @Author Michael Rainsford Ryan
#ifndef CELL_H
#define CELL_H

#include <SFML\Graphics.hpp>
#include "Globals.h"

class Cell
{
	Tile m_tileType;
	sf::IntRect m_texturePosition;
	sf::Vector2f m_position;

public:
	// Declare public function members
	Cell();

	inline Tile getTileType() { return m_tileType; } // Returns the type of the cell
	inline sf::IntRect getTexturePosition() { return m_texturePosition; } // Returns the texture rectangle of the cell
	//inline sf::Sprite getBody() { return body; } // Returns the sprite of the cell

	void setTileType(Tile t_tileType); // Sets the type of the cell
	inline void setPosition(sf::Vector2f t_position) { m_position = t_position; } // Sets the position of the cell
};

#endif // !CELL_H