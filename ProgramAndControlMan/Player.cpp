/// @Author Michael Rainsford Ryan
#include "Player.h"

Player::Player()
{
}

void Player::loadFiles()
{
	if (!m_spriteSheet.loadFromFile("ASSETS\\IMAGES\\yellowGhost32.png"))
	{
		// Error loading image
	}
	m_body.setTexture(m_spriteSheet);
	m_body.setTextureRect(sf::IntRect{ 0,0,32,32 });
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
		if (!t_maze[m_pos.y - 1][m_pos.x].getContainsWall())
		{
			m_pos.y--;
			m_body.setTextureRect(sf::IntRect{ 0,96,32,32 }); // Set the sprite to the look up texture
		}
	}
	else if (t_direction == Direction::South)
	{
		if (!t_maze[m_pos.y + 1][m_pos.x].getContainsWall())
		{
			m_pos.y++;
			m_body.setTextureRect(sf::IntRect{ 0,64,32,32 }); // Set the sprite to the look down texture
		}
	}
	else if (t_direction == Direction::West)
	{
		if (!t_maze[m_pos.y][m_pos.x - 1].getContainsWall())
		{
			m_pos.x--;
			m_body.setTextureRect(sf::IntRect{ 0,0,32,32 }); // Set the sprite to the look left texture
		}
	}
	else if (t_direction == Direction::East)
	{
		if (!t_maze[m_pos.y][m_pos.x + 1].getContainsWall())
		{
			m_pos.y++;
			m_body.setTextureRect(sf::IntRect{ 0,32,32,32 }); // Set the sprite to the look right texture
		}
	}

	m_body.setPosition(static_cast<sf::Vector2f>(m_pos * 32)); // Set the position to the current cell
}
