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
	m_score = 0;
	m_hurtTimer = 0;
	m_moveTimer = 0;
	m_characterDirection = 0;
	m_characterNumber = 0;
	m_lives = 3;
	setPos({ 12, 2 });
	m_body.setTextureRect(sf::IntRect{ m_character.x + CHAR_SPACING,m_character.y,CHAR_WIDTH,CHAR_HEIGHT });
	m_body.setColor(sf::Color::White);
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

/// <summary>
/// Save the score to a file if it's within the top ten scores.
/// </summary>
void Player::saveScoreToFile(std::string t_playerName)
{
	std::string names[MAX_PLAYERS]; // Setup the name string array
	int scores[MAX_PLAYERS]; // Setup the scores array
	int characterNums[MAX_PLAYERS]; // Setup the character numbers array

	readScore(names, scores, characterNums); // Read in data from the scoreboard file
	addScore(names, scores, characterNums, t_playerName); // Add the player score to the arrays if the score fits in the top 10
	writeScore(names, scores, characterNums); // Write the arrays back to the file
}

/// <summary>
/// Read from the player scores file and save the data to a set of arrays.
/// </summary>
/// <param name="t_names">Names array</param>
/// <param name="t_scores">Scores array</param>
/// <param name="t_characterNums">Character number array</param>
void Player::readScore(std::string t_names[], int t_scores[], int t_characterNums[])
{
	std::ifstream inputFile; // Create the file pointer
	inputFile.open("Data//scoreboard.txt"); // Open the file

	if (inputFile.is_open()) // Check that the file has opened successfully
	{
		std::string line; // Holds one line (one player) of data
		std::string item; // Holds one item of data
		int lineNum = 0; // The current line number

		while (std::getline(inputFile, line)) // Loop while getting lines to sort through
		{
			std::stringstream line_ss(line); // Create a string stream to sort through data
			int dataNum = 0; // The current data number

			while (std::getline(line_ss, item, ',')) // Loop through each piece of data of a line
			{
				if (item != "") // Make sure the item isn't empty
				{
					if (dataNum == 0) // Names
					{
						t_names[lineNum] = item;
					}
					else if (dataNum == 1) // Scores
					{
						t_scores[lineNum] = std::stoi(item);
					}
					else if (dataNum == 2) // Character number
					{
						t_characterNums[lineNum] = std::stoi(item);
					}
				}
				else
				{
					break; // Break if the data is blank
				}
				dataNum++; // Increment the data number
			} // End item loop

			lineNum++; // Increment the the line number
			if (lineNum >= MAX_PLAYERS)
			{
				break; // If the line number goes over the max number of player, break out
			}
		} // End line loop

		inputFile.close(); // Close the file
#ifdef _DEBUG
		std::cout << "File read success!" << std::endl; // Output that the file write was a success
#endif // DEBUG
	}
#ifdef _DEBUG
	else
	{
		std::cout << "Could not open scoreboard file." << std::endl; // Display an error if the file didn't open
	}
#endif // DEBUG
}

/// <summary>
/// <para>Adds the players score to a set of local arrays if it's higher</para>
/// <para>than any of the current scores.</para>
/// </summary>
/// <param name="t_names">Names array</param>
/// <param name="t_scores">Scores array</param>
/// <param name="t_characterNums">Character number</param>
/// <param name="t_playerName">Player name</param>
void Player::addScore(std::string t_names[], int t_scores[], int t_characterNums[], std::string t_playerName)
{
	for (int i = 0; i < MAX_PLAYERS; i++) // Loop through the player data arrays
	{
		if (m_score > t_scores[i]) // If the player score is greater than the current score
		{
			for (int j = MAX_PLAYERS - 1; j > i; j--) // Loop backwards through the array to move all items back
			{
				t_names[j] = t_names[j - 1]; // Move the name back one cell
				t_scores[j] = t_scores[j - 1]; // Move the score back one cell
				t_characterNums[j] = t_characterNums[j - 1]; // Move the character number
			}
			t_names[i] = t_playerName; // Set the player name to the cell
			t_scores[i] = m_score; // Set the player score to the cell
			t_characterNums[i] = m_characterNumber; // Set the player character number to the cell
			break; // Break once player data is placed
		}
	}
}

/// <summary>
/// Writes the player data arrays to a text file.
/// </summary>
/// <param name="t_names">Names array</param>
/// <param name="t_scores">Scores array</param>
/// <param name="t_characterNums">Character number array</param>
void Player::writeScore(std::string t_names[], int t_scores[], int t_characterNums[])
{
	std::ofstream outputFile; // Create an output file pointer
	outputFile.open("DATA//scoreboard.txt"); // Open the file

	if (outputFile.is_open()) // Check the file is open
	{
		for (int i = 0; i < MAX_PLAYERS; i++) // Loop through the player data array
		{
			if (t_names[i] == "") // Check if the cell is blank
			{
				break; // Break if the name is blank
			}
			outputFile << t_names[i] << ","; // Write the current name to the file
			outputFile << t_scores[i] << ","; // Write the current score to the file
			outputFile << t_characterNums[i] << ","; // Write the current character number to a file
			outputFile << std::endl; // Add a line break to the file
		}

		outputFile.close(); // Close the file
#ifdef _DEBUG
		std::cout << "File write success!" << std::endl; // Output that the file write was a success
#endif // DEBUG
	}
#ifdef _DEBUG
	else
	{
		std::cout << "Error opening file." << std::endl; // Output an error if the file cannot open
	}
#endif // DEBUG
}