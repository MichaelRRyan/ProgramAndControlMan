#include "WalkerEnemy.h"



WalkerEnemy::WalkerEnemy()
{
	loadFiles();
	m_moveDir = static_cast<Direction>(rand() % 4 + 1);
}

void WalkerEnemy::loadFiles()
{
	if (!m_spriteSheet.loadFromFile("ASSETS\\IMAGES\\redGhost32.png"))
	{
		// Error loading file
	}
	m_body.setTexture(m_spriteSheet);
	m_body.setTextureRect(sf::IntRect{ 0, 0, 32, 32 });
}

void WalkerEnemy::setPos(int t_row, int t_col)
{
	m_pos.x = t_col;
	m_pos.y = t_row;
}

void WalkerEnemy::move(Cell t_maze[][MAX_COLS])
{
	if (rand() % 10 == 0) // 1 in 10 chance of moving each frame
	{
		if (m_moveDir == Direction::North)
		{
			m_body.setTextureRect(sf::IntRect{ 0,96,32,32 }); // Set the sprite to the look up texture

			if (!t_maze[m_pos.y - 1][m_pos.x].getContainsWall())
			{
				m_pos.y--;
			}
			else
			{
				m_moveDir = static_cast<Direction>(rand() % 4 + 1);
			}
		}
		else if (m_moveDir == Direction::South)
		{
			m_body.setTextureRect(sf::IntRect{ 0,64,32,32 }); // Set the sprite to the look down texture
			if (!t_maze[m_pos.y + 1][m_pos.x].getContainsWall())
			{
				m_pos.y++;
			}
			else
			{
				m_moveDir = static_cast<Direction>(rand() % 4 + 1);
			}
		}
		else if (m_moveDir == Direction::West)
		{
			m_body.setTextureRect(sf::IntRect{ 0,32,32,32 }); // Set the sprite to the look left texture
			if (!t_maze[m_pos.y][m_pos.x - 1].getContainsWall())
			{
				m_pos.x--;
			}
			else
			{
				m_moveDir = static_cast<Direction>(rand() % 4 + 1);
			}
		}
		else if (m_moveDir == Direction::East)
		{
			m_body.setTextureRect(sf::IntRect{ 0,0,32,32 }); // Set the sprite to the look right texture
			if (!t_maze[m_pos.y][m_pos.x + 1].getContainsWall())
			{
				m_pos.x++;
			}
			else
			{
				m_moveDir = static_cast<Direction>(rand() % 4 + 1);
			}
		}

		m_body.setPosition(static_cast<sf::Vector2f>(m_pos * 32)); // Set the position to the current cell
	}
}
