/// @Author Michael Rainsford Ryan
#include "Player.h"

Player::Player()
{
	loadFiles();
	m_score = 0;
	m_canMove = true;
	m_hurtTimer = 0;
	m_lives = 3;
}

void Player::loadFiles()
{
	m_characterHeight = 64;
	m_characterWidthMargin = 22;

	if (!m_spriteSheet.loadFromFile("ASSETS\\IMAGES\\characters.png"))
	{
		// Error loading image
	}
	m_body.setTexture(m_spriteSheet);
	m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + m_characterWidthMargin) * 2,0,TILE_SIZE,m_characterHeight });
	m_body.setOrigin(0, TILE_SIZE);
}

void Player::setPos(sf::Vector2i t_pos)
{
	m_pos = t_pos;
	m_body.setPosition(static_cast<sf::Vector2f>(t_pos * 32));
}

void Player::move(Direction t_direction, Cell t_maze[][MAX_COLS])
{
	sf::Vector2i dirVector = Global::getDirectionVector(t_direction);
	sf::Vector2i desiredPosition = m_pos + dirVector; // Get the desired position based on the current position and direction

	if (t_maze[desiredPosition.y][desiredPosition.x].getTileType() != Tile::Rock) // Move if not blocked by a rock
	{
		if (t_maze[desiredPosition.y][desiredPosition.x].getTileType() != Tile::Moveable) // Move if not blocked by a moveable block
		{
			m_pos = desiredPosition; // Set the position to the desired one
		}
		else if (t_maze[desiredPosition.y + dirVector.y][desiredPosition.x + dirVector.x].getTileType() != Tile::Rock)
		{
			// Switch the tiles
			t_maze[desiredPosition.y][desiredPosition.x].setTileType(t_maze[desiredPosition.y + dirVector.y][desiredPosition.x + dirVector.x].getTileType());
			t_maze[desiredPosition.y + dirVector.y][desiredPosition.x + dirVector.x].setTileType(Tile::Moveable);
			m_pos = desiredPosition; // Set the position to the desired one
		}
	}

	switch (t_direction) // Set the direction texture for the sprite
	{
	case Direction::North:
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + m_characterWidthMargin) * 2,m_characterHeight * 2,TILE_SIZE,m_characterHeight }); // Set the sprite to the look up texture
		break;
	case Direction::South:
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + m_characterWidthMargin) * 2,0,TILE_SIZE,m_characterHeight }); // Set the sprite to the look down texture
		break;
	case Direction::West:
		m_body.setScale(-1.0f, 1.0f);
		m_body.setOrigin(TILE_SIZE, m_body.getOrigin().y);
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + m_characterWidthMargin) * 2,m_characterHeight * 1,TILE_SIZE,m_characterHeight }); // Set the sprite to the look left texture
		break;
	case Direction::East:
		m_body.setScale(1.0f, 1.0f);
		m_body.setOrigin(0.0f, m_body.getOrigin().y);
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + m_characterWidthMargin) * 2,m_characterHeight * 1,TILE_SIZE,m_characterHeight }); // Set the sprite to the look right texture
		break;
	}

	m_body.setPosition(static_cast<sf::Vector2f>(m_pos * 32)); // Set the position to the current cell

	if (t_maze[m_pos.y][m_pos.x].getTileType() == Tile::Coin) // If the cell contains a coin, pick it up
	{
		t_maze[m_pos.y][m_pos.x ].setTileType(Tile::None); // Remove coin
		m_score++; // Add to score
	}
}

void Player::update(GameState & t_gameState)
{
	if (m_hurtTimer > 0) // Decrement the hurt timer if it's greater than 0
	{
		m_hurtTimer--; // Decrement the timer
		if (m_hurtTimer == 0) // If the timer reaches zero set the player colour back to normal
			m_body.setColor(sf::Color::White);
	}
		
	if (m_lives <= 0) // If the player dies
	{
		t_gameState = GameState::GameOver;
	    m_lives = 0; // Set lives to 0 to avoid displaying -1
	}
}

void Player::checkCollision(WalkerEnemy & t_enemy)
{
	if (m_hurtTimer <= 0 && m_pos == t_enemy.getPos()) // If the player and enemy are colliding and the hurt timer is not greater than 0
	{
		m_lives--;
		m_hurtTimer = MAX_HURT_TIME;
		m_body.setColor(sf::Color::Red);
	}
}
