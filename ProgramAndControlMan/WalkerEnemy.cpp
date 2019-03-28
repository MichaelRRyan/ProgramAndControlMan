#include "WalkerEnemy.h"



WalkerEnemy::WalkerEnemy()
{
	loadFiles();
	m_moveDir = static_cast<Direction>(rand() % 4 + 1);
	m_moveTimer = 0;
}

void WalkerEnemy::loadFiles()
{
	m_characterNumber = { CHAR_SPACING, CHAR_HEIGHT * 3 };

	if (!m_spriteSheet.loadFromFile("ASSETS\\IMAGES\\characters.png"))
	{
		// Error loading image
	}
	m_body.setTexture(m_spriteSheet);
	m_body.setTextureRect(sf::IntRect{ m_characterNumber.x * 2,m_characterNumber.y,CHAR_WIDTH,CHAR_HEIGHT });
	m_body.setOrigin(0, CHAR_WIDTH);
}

void WalkerEnemy::setPos(int t_row, int t_col)
{
	m_pos.x = t_col;
	m_pos.y = t_row;

	m_previousPos = m_pos;
	m_body.setPosition(static_cast<sf::Vector2f>(m_pos * 32)); // Set the position to the current cell
}

void WalkerEnemy::move(Cell t_maze[][MAX_COLS], WalkerEnemy t_ghosts[])
{
	if (m_moveTimer <= 0) // The enemy can only move once its timer reaches zero
	{
		if (rand() % 6 == 0) // One in six chance each movement frames to change direction
		{
			m_moveDir = static_cast<Direction>(rand() % 4 + 1); // Find a new direction
		}

		m_previousPos = m_pos; // Set the previous position to the current one before moving

		for (int i = 0; i < 4; i++) // Loop until the enemy moves, finds a new direction or it tries four times (to stop infinite loops)
		{
			sf::Vector2i desiredPosition = m_pos + Global::getDirectionVector(m_moveDir); // Find the desired position from the current position and direction
			bool blocked = false; // True if the desired position holds another enemy or wall

			if (t_maze[desiredPosition.y][desiredPosition.x].getTileType() != Tile::Rock
				&& t_maze[desiredPosition.y][desiredPosition.x].getTileType() != Tile::Moveable) // Check if there's a rock blocking movement
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
		m_moveTimer = MOVEMENT_TIME; // Reset the move timer
	}
	else
	{
		m_moveTimer--;
		// Work out the new X and Y with Linear Interpolation
		float newX = (m_pos.x * 32) * (1.0f - (1.0f * m_moveTimer / MOVEMENT_TIME)) + (m_previousPos.x * 32) * (1.0f * m_moveTimer / MOVEMENT_TIME);
		float newY = (m_pos.y * 32) * (1.0f - (1.0f * m_moveTimer / MOVEMENT_TIME)) + (m_previousPos.y * 32) * (1.0f * m_moveTimer / MOVEMENT_TIME);
		m_body.setPosition(static_cast<float>(newX), static_cast<float>(newY)); // Set the position to the current cell
		int frameNum = static_cast<int>((1.0 * m_moveTimer / MOVEMENT_TIME) * 3);
		sf::IntRect frame = sf::IntRect{ m_characterNumber.x + (m_characterNumber.x * frameNum), m_characterNumber.y + m_characterDirection * CHAR_HEIGHT,CHAR_WIDTH, CHAR_HEIGHT };
		m_body.setTextureRect(frame);
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
		m_characterDirection = 2;
		break;
	case Direction::South: // Set the sprite to the look down texture
		m_characterDirection = 0;
		break;
	case Direction::West: // Set the sprite to the look left texture
		m_characterDirection = 1;
		m_body.setScale(-1.0f, 1.0f);
		m_body.setOrigin(CHAR_WIDTH, m_body.getOrigin().y);
		break;
	case Direction::East: // Set the sprite to the look right texture
		m_characterDirection = 1;
		m_body.setScale(1.0f, 1.0f);
		m_body.setOrigin(0.0f, m_body.getOrigin().y);
		break;
	default:
		break;
	}
}
