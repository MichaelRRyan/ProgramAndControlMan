#include "WalkerEnemy.h"



WalkerEnemy::WalkerEnemy()
{
	loadFiles();
	m_moveDir = static_cast<Direction>(rand() % 4 + 1);
	moveTimer = 0;
}

void WalkerEnemy::loadFiles()
{
	characterHeight = 64;
	characterWidthMargin = 22;

	if (!m_spriteSheet.loadFromFile("ASSETS\\IMAGES\\characters.png"))
	{
		// Error loading image
	}
	m_body.setTexture(m_spriteSheet);
	m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + characterWidthMargin) * 2,3,TILE_SIZE,characterHeight });
	m_body.setOrigin(0, TILE_SIZE);
}

void WalkerEnemy::setPos(int t_row, int t_col)
{
	m_pos.x = t_col;
	m_pos.y = t_row;

	m_body.setPosition(static_cast<sf::Vector2f>(m_pos * 32)); // Set the position to the current cell
}

void WalkerEnemy::move(Cell t_maze[][MAX_COLS], WalkerEnemy t_ghosts[])
{
	if (moveTimer <= 0) // The enemy can only move once its timer reaches zero
	{
		if (rand() % 6 == 0) // One in six chance each movement frames to change direction
		{
			m_moveDir = static_cast<Direction>(rand() % 4 + 1); // Find a new direction
		}

		for (int i = 0; i < 4; i++) // Loop until the enemy moves, finds a new direction or it tries four times (to stop infinite loops)
		{
			sf::Vector2i desiredPosition = m_pos + Global::getDirectionVector(m_moveDir); // Find the desired position from the current position and direction
			bool blocked = false; // True if the desired position holds another enemy or wall

			if (t_maze[desiredPosition.y][desiredPosition.x].getTileType() != Tile::Rock) // Check if there's a rock blocking movement
			{
				for (int i = 0; i < MAX_GHOSTS; i++) // Loop through other ghosts
				{
					if (t_ghosts[i].getPos() == desiredPosition) // Check if another ghost is blocking the movement
					{
						blocked = true; // Movement is blocked
						break; // Break from loop
					}
				}
			}
			else
			{
				blocked = true; // Movement is blocked
			}

			// Move if not blocked else change direction
			if (!blocked)
			{
				m_pos = desiredPosition;
				break; // Break from the loop if the enemy can move
			}
			else
			{
				m_moveDir = static_cast<Direction>(rand() % 4 + 1); // Find a new direction
			}
				
		}
		
		setTextureDirection(); // Set the texture to the direction
		m_body.setPosition(static_cast<sf::Vector2f>(m_pos * 32)); // Set the position to the current cell
		moveTimer = MOVEMENT_TIME; // Reset the move timer
	}
	else
	{
		moveTimer--;
	}
}

/// <summary>
/// Switch the texture rectangle to change the facing direction
/// </summary>
void WalkerEnemy::setTextureDirection()
{
	switch (m_moveDir)
	{
	case Direction::North: // Set the sprite to the look up texture
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + characterWidthMargin) * 2,characterHeight * 5,TILE_SIZE,characterHeight });
		break;
	case Direction::South: // Set the sprite to the look down texture
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + characterWidthMargin) * 2,characterHeight * 3,TILE_SIZE,characterHeight });
		break;
	case Direction::West: // Set the sprite to the look left texture
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + characterWidthMargin) * 2,characterHeight * 4,TILE_SIZE,characterHeight });
		m_body.setScale(-1.0f, 1.0f);
		m_body.setOrigin(TILE_SIZE, m_body.getOrigin().y);
		break;
	case Direction::East: // Set the sprite to the look right texture
		m_body.setTextureRect(sf::IntRect{ (TILE_SIZE + characterWidthMargin) * 2,characterHeight * 4,TILE_SIZE,characterHeight });
		m_body.setScale(1.0f, 1.0f);
		m_body.setOrigin(0.0f, m_body.getOrigin().y);
		break;
	default:
		break;
	}
}
