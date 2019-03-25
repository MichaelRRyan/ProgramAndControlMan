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

	m_body.setPosition(static_cast<sf::Vector2f>(m_pos * 32)); // Set the position to the current cell
}

void WalkerEnemy::move(Cell t_maze[][MAX_COLS], WalkerEnemy t_ghosts[])
{
	if (rand() % 10 == 0) // 1 in 10 chance of moving each frame
	{
		sf::Vector2i desiredPosition = m_pos + Global::getDirectionVector(m_moveDir);
		bool blocked = false;

		if (!t_maze[desiredPosition.y][desiredPosition.x].getContainsWall())
		{
			for (int i = 0; i < MAX_GHOSTS; i++)
			{
				if (t_ghosts[i].getPos() == desiredPosition)
				{
					blocked = true;
					break;
				}
			}
		}
		else
		{
			blocked = true;
		}

		// Move if not blocked
		if (!blocked)
		{
			m_pos = desiredPosition;
		}
		else
		{
			m_moveDir = static_cast<Direction>(rand() % 4 + 1);
		}

		// Switch the texture rectangle to change the facing direction
		switch (m_moveDir)
		{
		case Direction::North:
			m_body.setTextureRect(sf::IntRect{ 0,96,32,32 }); // Set the sprite to the look up texture
			break;
		case Direction::South:
			m_body.setTextureRect(sf::IntRect{ 0,64,32,32 }); // Set the sprite to the look down texture
			break;
		case Direction::West:
			m_body.setTextureRect(sf::IntRect{ 0,32,32,32 }); // Set the sprite to the look left texture
			break;
		case Direction::East:
			m_body.setTextureRect(sf::IntRect{ 0,0,32,32 }); // Set the sprite to the look right texture
			break;
		default:
			break;
		}

		m_body.setPosition(static_cast<sf::Vector2f>(m_pos * 32)); // Set the position to the current cell
	}
}
