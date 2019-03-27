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
	loadFiles();
	m_score = 0;
	m_hurtTimer = 0;
	m_moveTimer = 0;
	m_characterDirection = 0;
	m_lives = 3;
}

void Player::loadFiles()
{
	if (!m_spriteSheet.loadFromFile("ASSETS\\IMAGES\\characters.png"))
	{
		// Error loading image
	}

	m_characterNumber = { CHAR_SPACING * 5, CHAR_HEIGHT * 24 };
	m_body.setTexture(m_spriteSheet);
	m_body.setTextureRect(sf::IntRect{ m_characterNumber.x + CHAR_SPACING,m_characterNumber.y,CHAR_WIDTH,CHAR_HEIGHT });
	m_body.setOrigin(0, CHAR_WIDTH);
}

void Player::setPos(sf::Vector2i t_pos)
{
	m_pos = t_pos;
	m_body.setPosition(static_cast<sf::Vector2f>(t_pos * 32));
}

/// <summary>
/// Sets the player sprite to the character from the array with the inputted index.
/// If the number is outside of the bounds, the number will overflow/underflow to another.
/// </summary>
/// <param name="t_characterNum"></param>
void Player::setCharacter(int t_characterNum)
{
	int charNum = t_characterNum % MAX_CHARACTERS; // Manage overflow
	if (charNum < 0) // Manage underflow
		charNum = MAX_CHARACTERS + charNum;
	m_characterNumber = m_characterPositions[charNum]; // Set the correct index
	m_body.setTextureRect(sf::IntRect{ m_characterNumber.x + CHAR_SPACING,m_characterNumber.y,CHAR_WIDTH,CHAR_HEIGHT }); // Set the texture to the sprite
}

void Player::move(Direction t_direction, Cell t_maze[][MAX_COLS])
{
	sf::Vector2i dirVector = Global::getDirectionVector(t_direction);
	sf::Vector2i desiredPosition = m_pos + dirVector; // Get the desired position based on the current position and direction

	if (t_maze[desiredPosition.y][desiredPosition.x].getTileType() != Tile::Rock) // Move if not blocked by a rock
	{
		if (t_maze[desiredPosition.y][desiredPosition.x].getTileType() != Tile::Moveable) // Move if not blocked by a moveable block
		{
			m_previousPos = m_pos;
			m_pos = desiredPosition; // Set the position to the desired one
			m_moveTimer = MOVEMENT_TIME;
		}
		else if (t_maze[desiredPosition.y + dirVector.y][desiredPosition.x + dirVector.x].getTileType() != Tile::Rock)
		{
			// Switch the tiles
			t_maze[desiredPosition.y][desiredPosition.x].setTileType(t_maze[desiredPosition.y + dirVector.y][desiredPosition.x + dirVector.x].getTileType());
			t_maze[desiredPosition.y + dirVector.y][desiredPosition.x + dirVector.x].setTileType(Tile::Moveable);
			m_previousPos = m_pos;
			m_pos = desiredPosition; // Set the position to the desired one
			m_moveTimer = MOVEMENT_TIME;
		}
	}

	switch (t_direction) // Set the direction texture for the sprite
	{
	case Direction::North:
		m_characterDirection = 2;
		break;
	case Direction::South:
		m_characterDirection = 0;
		break;
	case Direction::West:
		m_body.setScale(-1.0f, 1.0f);
		m_body.setOrigin(CHAR_WIDTH, m_body.getOrigin().y);
		m_characterDirection = 1;
		break;
	case Direction::East:
		m_body.setScale(1.0f, 1.0f);
		m_body.setOrigin(0.0f, m_body.getOrigin().y);
		m_characterDirection = 1;
		break;
	}

	if (t_maze[m_pos.y][m_pos.x].getTileType() == Tile::Coin) // If the cell contains a coin, pick it up
	{
		t_maze[m_pos.y][m_pos.x ].setTileType(Tile::None); // Remove coin
		m_score++; // Add to score
	}
}

void Player::update(Cell t_maze[][MAX_COLS], GameState & t_gameState)
{
	if (m_moveTimer == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			move(Direction::North, t_maze);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			move(Direction::South, t_maze);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			move(Direction::East, t_maze);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			move(Direction::West, t_maze);
		}

		m_body.setTextureRect(sf::IntRect{ m_characterNumber.x + CHAR_SPACING,m_characterNumber.y + m_characterDirection * CHAR_HEIGHT,CHAR_WIDTH,CHAR_HEIGHT });
	}
	else
	{
		m_moveTimer--;
		// Work out the new X and Y with Linear Interpolation
		float newX = (m_pos.x * 32) * (1.0f - (1.0f * m_moveTimer / MOVEMENT_TIME)) + (m_previousPos.x * 32) * (1.0f * m_moveTimer / MOVEMENT_TIME);
		float newY = (m_pos.y * 32) * (1.0f - (1.0f * m_moveTimer / MOVEMENT_TIME)) + (m_previousPos.y * 32) * (1.0f * m_moveTimer / MOVEMENT_TIME);
		m_body.setPosition(static_cast<float>(newX), static_cast<float>(newY)); // Set the position to the current cell

		int frameNum = static_cast<int>((1.0 * m_moveTimer / MOVEMENT_TIME) * 3);
		sf::IntRect frame = sf::IntRect{ m_characterNumber.x + (CHAR_SPACING * frameNum), m_characterNumber.y + (m_characterDirection * CHAR_HEIGHT),CHAR_WIDTH, CHAR_HEIGHT };
		m_body.setTextureRect(frame);
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
