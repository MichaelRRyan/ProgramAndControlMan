/// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Cell.h"
#include "WalkerEnemy.h"

class Player
{
	// Declare private data members
	const int MAX_HURT_TIME{ 60 }; // The maximum time the player can be invincible for after being damaged
	const int MOVEMENT_TIME{ 15 }; // Time delay between each player movement
	static const int MAX_CHARACTERS{ 10 }; // Number of character the player can play as

	sf::Texture m_spriteSheet;
	sf::Sprite m_body;
	sf::Vector2i m_pos;
	sf::Vector2i m_previousPos; // Used for animation
	int m_score;
	int m_lives;
	int m_hurtTimer; // The timer the player can be invincible for after being damaged
	int m_moveTimer;

	// Texture and animation
	sf::Vector2i m_characterPositions[MAX_CHARACTERS]; // The base position of each character on the sprite sheet for the player to choose from
	int m_characterDirection;
	sf::Vector2i m_characterNumber; // The number of pixels from the top left of the sprite sheet to reach the player sprite

public:
	// Declare public function members
	Player();
	void loadFiles();

	void setPos(sf::Vector2i t_pos); // Set the row and column position of the player
	inline void setScore(int t_score) { m_score = t_score; }
	inline void setLives(int t_lives) { m_lives = t_lives; } // Set the number of lives for the player
	inline void setPosition(sf::Vector2f t_position) { m_body.setPosition(t_position); } // Sets the position of the player sprite
	inline void setScale(sf::Vector2f t_scale) { m_body.setScale(t_scale); } // Sets the scale of the player sprite
	inline void refreshPosition() { m_body.setPosition(static_cast<float>(m_pos.x * TILE_SIZE), static_cast<float>(m_pos.y * TILE_SIZE)); } // Resets the player sprite position to the row and col
	void setCharacter(int t_characterNum); // Selects the character from the character array with the inputted index

	inline sf::Vector2i getPos() { return m_pos; } // get the row and col position of the player
	inline sf::Sprite getBody() { return m_body; }
	inline int getScore() { return m_score; } // Returns the score of the player
	inline int getLives() { return m_lives; } // Returns the lives of the player

	void move(Direction t_direction, Cell t_maze[][MAX_COLS]);
	void update(Cell t_maze[][MAX_COLS], GameState &t_gameState);
	void checkCollision(WalkerEnemy &t_enemy);
};

