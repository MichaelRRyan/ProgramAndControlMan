/// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Globals.h"

class Cell
{
	// Declare private data members
	sf::Texture wallTexture;
	sf::Texture coinTexture;
	sf::Texture blankTexture;

	sf::Sprite body;

	bool containsWall;
	bool containsCoin;

public:
	// Declare public function members
	Cell();
	void loadFiles();

	inline bool getContainsWall() { return containsWall; } // Returns whether or not the cell contains a wall
	inline bool getContainsCoin() { return containsCoin; } // Returns whether or not the cell contains a coin
	inline sf::Sprite getBody() { return body; } // Returns the sprite of the cell

	void setContainsWall(bool t_wall); // Sets the cell to have a wall or not
	void setContainsCoin(bool t_coin); // Sets the cell to have a coin or not
	inline void setPosition(sf::Vector2f t_position) { body.setPosition(t_position); } // Sets the position of the cell
};

