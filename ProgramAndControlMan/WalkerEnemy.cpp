#include "WalkerEnemy.h"


/// <summary>
/// <para>Enemy default constructer.</para>
/// <para>Load texture files, set the move direction, set the move timer,</para>
/// <para>set the sight range and following player bool</para>
/// </summary>
WalkerEnemy::WalkerEnemy()
{
	loadFiles();
	m_moveDir = static_cast<Direction>(rand() % 4 + 1);
	m_moveTimer = 0;
	sightRange = 5; // Enemy can see the player five tiles away
	followingPlayer = false;
}

/// <summary>
/// Load the texture file and apply it to the sprite.
/// </summary>
void WalkerEnemy::loadFiles()
{
	m_characterNumber = { CHAR_SPACING, CHAR_HEIGHT * 3 };

	if (!m_spriteSheet.loadFromFile("ASSETS\\IMAGES\\characters.png"))
	{
		// Error loading image
	}
	m_body.setTexture(m_spriteSheet);
	m_body.setTextureRect(sf::IntRect{ m_characterNumber.x * 2,m_characterNumber.y,CHAR_WIDTH,CHAR_HEIGHT });
	m_body.setOrigin(0.0f, static_cast<float>(CHAR_WIDTH));
}

/// <summary>
/// <para>Set the row and column of the enemy.</para>
/// <para>Set the previous position and the sprite position.</para>
/// </summary>
/// <param name="t_row">Row</param>
/// <param name="t_col">Column</param>
void WalkerEnemy::setPos(int t_row, int t_col)
{
	m_pos.x = t_col; // Set the column
	m_pos.y = t_row; // Set the row

	m_previousPos = m_pos; // Set the previous position for animation
	m_body.setPosition(static_cast<sf::Vector2f>(m_pos * 32)); // Set the position to the current cell
}

/// <summary>
/// <para>Move the enemy in its current move direction.</para>
/// <para>Checks each frame for a player and switch direction if found</para>
/// <para>Enemy has a one in six chance to change direction randomly.</para>
/// <para>Checks that the path isn't blocked by a wall or an enemy.</para>
/// <para>Changes direction if blocked, move in direction if not.</para>
/// <para>Set the texture direction and move timer.</para>
/// </summary>
/// <param name="t_maze"></param>
/// <param name="t_ghosts"></param>
void WalkerEnemy::move(Cell t_maze[][MAX_COLS], WalkerEnemy t_ghosts[], Player t_player)
{
	checkForPlayer(t_maze, t_player); // Check for player
	
	if (m_moveTimer <= 0) // The enemy can only move once its timer reaches zero
	{
		if (rand() % 6 == 0 && !followingPlayer) // One in six chance each movement frames to change direction if not found player
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
		m_body.setOrigin(static_cast<float>(CHAR_WIDTH), m_body.getOrigin().y);
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

/// <summary>
/// <para>Checks north, south, east and west within the sight range for the player</para>
/// <para>and sets the direction and following player bool if found.</para>
/// </summary>
/// <param name="t_maze"></param>
void WalkerEnemy::checkForPlayer(Cell t_maze[][MAX_COLS], Player t_player)
{
	bool followingPlayer = false;
	Direction checkDirection = Direction::North; // Set the check direction to begin with north

	for (int i = 0; i < 4; i++) // Check in each direction
	{
		for (int j = 1; j <= sightRange; j++) // Check for player in current direction
		{
			// Get the check direction by the direction vector multiplied by the iteration and current position 
			sf::Vector2i checkPosition = m_pos + (Global::getDirectionVector(checkDirection) * j);

			if (t_maze[checkPosition.y][checkPosition.x].getTileType() == Tile::Rock
				|| t_maze[checkPosition.y][checkPosition.x].getTileType() == Tile::Moveable)
			{
				break; // Wall blocking sight, break from loop
			}
			else if (t_player.getPos() == checkPosition) // Check for player
			{
				followingPlayer = true; // Now following player
				m_moveDir = checkDirection; // Set the move direction to the current check direction
				break; // Break out of the loop
			}
		} // End for (tile)

		if (followingPlayer) // Break if already found the player
			break;

		switch (checkDirection) // Switch to the next direction to check
		{
		case Direction::North:
			checkDirection = Direction::South;
			break;
		case Direction::South:
			checkDirection = Direction::West;
			break;
		case Direction::West:
			checkDirection = Direction::East;
			break;
		}
	} // End for (direction)
}

