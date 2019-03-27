/// @Author Michael Rainsford Ryan
#pragma once

#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Cell.h"
#include "WalkerEnemy.h"

class Player
{
	// Declare private data members
	const int MAX_HURT_TIME = 60; // The maximum time the player can be invincible for after being damaged

	sf::Texture m_spriteSheet;
	sf::Sprite m_body;
	sf::Vector2i m_pos;
	int m_score;
	bool m_canMove;
	int m_lives;
	int m_hurtTimer; // The timer the player can be invincible for after being damaged

	// Texture variables
	int m_characterHeight;
	int m_characterWidthMargin;

public:
	// Declare public function members
	Player();
	void loadFiles();

	void setPos(sf::Vector2i t_pos); // Set the row and column position of the player
	inline void setCanMove(bool t_canMove) { m_canMove = t_canMove; } // Sets the canMove state of the player
	inline void setScore(int t_score) { m_score = t_score; }
	inline void setLives(int t_lives) { m_lives = t_lives; } // Set the number of lives for the player

	inline sf::Vector2i getPos() { return m_pos; } // get the row and col position of the player
	inline sf::Sprite getBody() { return m_body; }
	inline int getScore() { return m_score; } // Returns the score of the player
	inline int getLives() { return m_lives; } // Returns the lives of the player
	inline bool getCanMove() { return m_canMove;  } // Returns the canMove state of the player

	void move(Direction t_direction, Cell t_maze[][MAX_COLS]);
	void update(GameState &t_gameState);
	void checkCollision(WalkerEnemy &t_enemy);
};

