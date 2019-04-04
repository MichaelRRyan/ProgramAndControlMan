/// @Author Michael Rainsford Ryan
#include "Player.h"

Player::Player() :
	// Setup the character positions 
	m_characterPositions{
	{ CHAR_SPACING * 5, CHAR_HEIGHT * 24 },
	{ CHAR_SPACING * 5, CHAR_HEIGHT * 27},
	{ CHAR_SPACING * 6, CHAR_HEIGHT * 13},
	{ CHAR_SPACING * 11, CHAR_HEIGHT * 13},
	{ CHAR_SPACING * 11, CHAR_HEIGHT * 17},
	{ CHAR_SPACING * 1, 0},
	{ CHAR_SPACING * 11, 0},
	{ CHAR_SPACING * 8, CHAR_HEIGHT * 9},
	{ CHAR_SPACING * 1, CHAR_HEIGHT * 16},
	{ CHAR_SPACING * 1, CHAR_HEIGHT * 30} }
{
	// Initialise the player variables
	loadFiles();
	respawn();
}

/// <summary>
/// Load the player texture files and set up the sprite.
/// </summary>
void Player::loadFiles()
{
	if (!m_spriteSheet.loadFromFile("ASSETS\\IMAGES\\characters.png"))
	{
		// Error loading image
	}

	m_body.setTexture(m_spriteSheet); // Set the player texture
	m_body.setTextureRect(sf::IntRect{ CHAR_SPACING * 2,0,CHAR_WIDTH,CHAR_HEIGHT }); // Set the base character texture rectangle
	m_body.setOrigin(0.0f, static_cast<float>(CHAR_WIDTH)); // Set he origin of the player to ignore the top of the sprite
}

/// <summary>
/// Setup the initial and respawn player values.
/// </summary>
void Player::respawn()
{
	m_score = 0; // Reset the score to 0
	m_hurtTimer = 0; // Set the hurt timer to zero
	m_moveTimer = 0; // Set the move timer to zero
	m_characterDirection = 0; // Reset the character direction to 0
	m_lives = 3; // Reset the lives to 3
	m_body.setTextureRect(sf::IntRect{ m_character.x + CHAR_SPACING,m_character.y,CHAR_WIDTH,CHAR_HEIGHT }); // Set the texture rectangle
	m_body.setColor(sf::Color::White); // Set the colour of the sprite to white
	m_body.setOrigin(0.0f, m_body.getOrigin().y); // reset the origin of the sprite
	m_body.setScale(1.0f, 1.0f); // Reset the scale of the sprite
	setPos({ 12, 2 }); // Reset the position of the player
}

/// <summary>
/// Set the player position to the row and column inputted.
/// Sets the previous position and the sprite position to the new position.
/// </summary>
/// <param name="t_pos">x = col, y = row</param>
void Player::setPos(sf::Vector2i t_pos)
{
	m_pos = t_pos; // Set the new row and col
	m_previousPos = t_pos; // Set the previous position to the new one
	m_body.setPosition(static_cast<sf::Vector2f>(t_pos * 32)); // Set the sprite position
}

/// <summary>
/// Sets the player sprite to the character from the array with the inputted index.
/// If the number is outside of the bounds, the number will overflow/underflow to another.
/// </summary>
/// <param name="t_characterNum"></param>
void Player::setCharacter(int t_characterNum)
{
	m_characterNumber = t_characterNum % MAX_CHARACTERS; // Manage overflow
	if (m_characterNumber < 0) // Manage underflow
		m_characterNumber = MAX_CHARACTERS + m_characterNumber;
	m_character = m_characterPositions[m_characterNumber]; // Set the correct index
	m_body.setTextureRect(sf::IntRect{ m_character.x + CHAR_SPACING,m_character.y,CHAR_WIDTH,CHAR_HEIGHT }); // Set the texture to the sprite
}

/// <summary>
/// Move the player in the inputted direction.
/// Checks for walls before moving and picks up coins.
/// Moveable blocks get moved if nothing behind them.
/// </summary>
/// <param name="t_direction">Movement direction</param>
/// <param name="t_maze">Maze array</param>
void Player::move(Direction t_direction, Cell t_maze[][MAX_COLS])
{
	sf::Vector2i dirVector = Global::getDirectionVector(t_direction); // Get a vector form of the movement direction
	sf::Vector2i desiredPosition = m_pos + dirVector; // Get the desired position based on the current position and direction

	if (t_maze[desiredPosition.y][desiredPosition.x].getTileType() != Tile::Rock) // Move if not blocked by a rock
	{
		if (t_maze[desiredPosition.y][desiredPosition.x].getTileType() != Tile::Moveable) // Move if not blocked by a moveable block
		{
			m_previousPos = m_pos; // Set the previous position to the current one
			m_pos = desiredPosition; // Set the current position to the desired one
			m_moveTimer = MOVEMENT_TIME; // Set the movement timer to add movement delay
		}
		else if (t_maze[desiredPosition.y + dirVector.y][desiredPosition.x + dirVector.x].getTileType() != Tile::Rock
				&& t_maze[desiredPosition.y + dirVector.y][desiredPosition.x + dirVector.x].getTileType() != Tile::Moveable)
		{
			// Switch the tiles
			t_maze[desiredPosition.y][desiredPosition.x].setTileType(t_maze[desiredPosition.y + dirVector.y][desiredPosition.x + dirVector.x].getTileType());
			t_maze[desiredPosition.y + dirVector.y][desiredPosition.x + dirVector.x].setTileType(Tile::Moveable);
			m_previousPos = m_pos;
			m_pos = desiredPosition; // Set the position to the desired one
			m_moveTimer = MOVEMENT_TIME;
		}
	}

	setTextureDirection(t_direction); // Set the direction of the sprite to the movement direction

	if (t_maze[m_pos.y][m_pos.x].getTileType() == Tile::Coin) // If the cell contains a coin, pick it up
	{
		t_maze[m_pos.y][m_pos.x ].setTileType(Tile::None); // Remove coin
		m_score++; // Add to score
	}
}

/// <summary>
/// Set the sprite direction and scale of the player to the current direction.
/// Sets the sprite direction so the tecture can be set in the update.
/// </summary>
/// <param name="t_direction">Movement direction</param>
void Player::setTextureDirection(Direction t_direction)
{
	// Set the direction texture for the sprite
	switch (t_direction)
	{
	case Direction::North:
		m_characterDirection = 2;
		break;
	case Direction::South:
		m_characterDirection = 0;
		break;
	case Direction::West:
		m_body.setScale(-1.0f, 1.0f);
		m_body.setOrigin(static_cast<float>(CHAR_WIDTH), m_body.getOrigin().y);
		m_characterDirection = 1;
		break;
	case Direction::East:
		m_body.setScale(1.0f, 1.0f);
		m_body.setOrigin(0.0f, m_body.getOrigin().y);
		m_characterDirection = 1;
		break;
	}
}

/// <summary>
/// Update the player object.
/// Checks for movement input and moves the player if the move timer is zero.
/// Animates the player movement and sets the still sprites.
/// Decrements the hurt timer and checks if the player is still alive.
/// </summary>
/// <param name="t_maze">Maze array</param>
/// <param name="t_gameState">Current game state</param>
void Player::update(Cell t_maze[][MAX_COLS], GameState & t_gameState)
{
	if (m_moveTimer == 0) // the player can move if the movement timer is zero
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // Upwards movement
		{
			move(Direction::North, t_maze);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // Downwards movement
		{
			move(Direction::South, t_maze);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Right movement
		{
			move(Direction::East, t_maze);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Left movement
		{
			move(Direction::West, t_maze);
		}

		// Set the standing sprite of the player
		m_body.setTextureRect(sf::IntRect{ m_character.x + CHAR_SPACING,m_character.y + m_characterDirection * CHAR_HEIGHT,CHAR_WIDTH,CHAR_HEIGHT });
	}
	else
	{
		m_moveTimer--; // Decrement the movement timer
		// Work out the new X and Y with Linear Interpolation
		float newX = (m_pos.x * 32) * (1.0f - (1.0f * m_moveTimer / MOVEMENT_TIME)) + (m_previousPos.x * 32) * (1.0f * m_moveTimer / MOVEMENT_TIME);
		float newY = (m_pos.y * 32) * (1.0f - (1.0f * m_moveTimer / MOVEMENT_TIME)) + (m_previousPos.y * 32) * (1.0f * m_moveTimer / MOVEMENT_TIME);
		m_body.setPosition(static_cast<float>(newX), static_cast<float>(newY)); // Set the position to the current cell

		int frameNum = static_cast<int>((1.0 * m_moveTimer / MOVEMENT_TIME) * 3); // Work out the animation frame number based off the movement timer
		m_body.setTextureRect(sf::IntRect{ m_character.x + (CHAR_SPACING * frameNum), m_character.y + (m_characterDirection * CHAR_HEIGHT),CHAR_WIDTH, CHAR_HEIGHT });
	}

	if (m_hurtTimer > 0) // Decrement the hurt timer if it's greater than 0
	{
		m_hurtTimer--; // Decrement the timer
		if (m_hurtTimer == 0) // If the timer reaches zero set the player colour back to normal
			m_body.setColor(sf::Color::White);
	}
		
	if (m_lives <= 0) // If the player dies
	{
		t_gameState = GameState::GameOver;
		m_body.setColor(sf::Color::White);
	    m_lives = 0; // Set lives to 0 to avoid displaying -1
	}
}

/// <summary>
/// Checks collisions against a ghost enemy.
/// If the hurt timer is zero and colliding with an enemy, take damage.
/// </summary>
/// <param name="t_enemy"></param>
void Player::checkCollision(WalkerEnemy & t_enemy)
{
	if (m_hurtTimer <= 0 && m_pos == t_enemy.getPos()) // If the player and enemy are colliding and the hurt timer is not greater than 0
	{
		m_lives--; // Decrement the lives
		m_hurtTimer = MAX_HURT_TIME; // Set the hurt timer for temporary invincibilty
		m_body.setColor(sf::Color::Red); // Set the player colour to red to show injury
	}
}