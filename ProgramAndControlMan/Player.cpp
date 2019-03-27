/// @Author Michael Rainsford Ryan
#include "Player.h"

Player::Player()
{
	loadFiles();
	m_score = 0;
	m_canMove = true;
}

void Player::loadFiles()
{
	characterHeight = 64;
	characterWidthMargin = 22;

	if (!m_spriteSheet.loadFromFile("ASSETS\\IMAGES\\characters.png"))
	{
		// Error loading image
	}
	m_body.setTexture(m_spriteSheet);
	m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + characterWidthMargin) * 2,0,TILE_SIZE,characterHeight });
	m_body.setOrigin(0, TILE_SIZE);
}

void Player::setPos(sf::Vector2i t_pos)
{
	m_pos = t_pos;
	m_body.setPosition(static_cast<sf::Vector2f>(t_pos * 32));
}

void Player::move(Direction t_direction, Cell t_maze[][MAX_COLS])
{
	if (t_direction == Direction::North)
	{
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + characterWidthMargin) * 2,characterHeight * 2,TILE_SIZE,characterHeight }); // Set the sprite to the look up texture

		if (!t_maze[m_pos.y - 1][m_pos.x].getContainsWall())
		{
			m_pos.y--;
		}
	}
	else if (t_direction == Direction::South)
	{
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + characterWidthMargin) * 2,0,TILE_SIZE,characterHeight }); // Set the sprite to the look down texture
		if (!t_maze[m_pos.y + 1][m_pos.x].getContainsWall())
		{
			m_pos.y++;
		}
	}
	else if (t_direction == Direction::West)
	{
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + characterWidthMargin) * 2,characterHeight * 1,TILE_SIZE,characterHeight }); // Set the sprite to the look left texture
		m_body.setScale(-1.0f, 1.0f);
		m_body.setOrigin(TILE_SIZE, m_body.getOrigin().y);
		if (!t_maze[m_pos.y][m_pos.x - 1].getContainsWall())
		{
			m_pos.x--;
		}
	}
	else if (t_direction == Direction::East)
	{
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + characterWidthMargin) * 2,characterHeight * 1,TILE_SIZE,characterHeight }); // Set the sprite to the look right texture
		m_body.setScale(1.0f, 1.0f);
		m_body.setOrigin(0.0f, m_body.getOrigin().y);
		if (!t_maze[m_pos.y][m_pos.x + 1].getContainsWall())
		{
			m_pos.x++;
		}
	}

	m_body.setPosition(static_cast<sf::Vector2f>(m_pos * 32)); // Set the position to the current cell

	if (t_maze[m_pos.y][m_pos.x].getContainsCoin())
	{
		t_maze[m_pos.y][m_pos.x ].setContainsCoin(false);
		m_score++;
	}
}
