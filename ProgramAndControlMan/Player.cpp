/// @Author Michael Rainsford Ryan
#include "Player.h"

Player::Player()
{
	loadFiles();
	m_score = 0;
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
		m_body.setTextureRect(sf::IntRect{ 0,96,32,32 }); // Set the sprite to the look up texture

		if (!t_maze[m_pos.y - 1][m_pos.x].getContainsWall())
		{
			m_pos.y--;
		}
	}
	else if (t_direction == Direction::South)
	{
		m_body.setTextureRect(sf::IntRect{ 0,64,32,32 }); // Set the sprite to the look down texture
		if (!t_maze[m_pos.y + 1][m_pos.x].getContainsWall())
		{
			m_pos.y++;
		}
	}
	else if (t_direction == Direction::West)
	{
		m_body.setTextureRect(sf::IntRect{ 0,32,32,32 }); // Set the sprite to the look left texture
		if (!t_maze[m_pos.y][m_pos.x - 1].getContainsWall())
		{
			m_pos.x--;
		}
	}
	else if (t_direction == Direction::East)
	{
		m_body.setTextureRect(sf::IntRect{ 0,0,32,32 }); // Set the sprite to the look right texture
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
