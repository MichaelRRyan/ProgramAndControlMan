#include "Screens.h"


/// <summary>
/// Default constructer and setup for the game screens.
/// </summary>
Screens::Screens() :
	m_gameOver{ false } // Initialse the game over bool
{
	loadFiles(); // Load the font and texture files
	setupText(); // Setup the text objects

	m_backgroundSprite.setTexture(m_backgroundTexture); // Set the background texture to the sprite

	m_buttonSprite.setTexture(m_buttonTexture);
	m_buttonSprite.setTextureRect(sf::IntRect{ BUTTON_IMAGE_WIDTH,45,BUTTON_IMAGE_WIDTH,BUTTON_IMAGE_HEIGHT });
	m_buttonSprite.setOrigin(BUTTON_IMAGE_WIDTH / 2, BUTTON_IMAGE_HEIGHT / 2);
	m_buttonSprite.setScale(1.8f, 1.8f);

	m_arrowSprite.setTexture(m_buttonTexture);
	m_arrowSprite.setTextureRect(sf::IntRect{ 339,143,39,31 });

	m_characterNumber = 0;
}

/// <summary>
/// Load game files.
/// Load textures and fonts.
/// </summary>
void Screens::loadFiles()
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\pacmanBackground.jpg"))
	{
		// Error loading background sprite
	}
	if (!m_buttonTexture.loadFromFile("ASSETS\\IMAGES\\yellowSheet.png"))
	{
		// Error loading background sprite
	}
	if (!m_twosonFont.loadFromFile("ASSETS\\FONTS\\twoson.ttf"))
	{
		// Error loading font file
	}
}

/// <summary>
/// Setup all the text objects with the pacman font,
/// correct size, position, colour and string.
/// </summary>
void Screens::setupText()
{
	m_titleText.setFont(m_twosonFont);
	m_titleText.setCharacterSize(80u);
	m_titleText.setString("PACMAN");
	m_titleText.setPosition(400.0f, 80.0f);
	m_titleText.setOrigin(m_titleText.getGlobalBounds().width / 2, 0);

	m_buttonText.setFont(m_twosonFont);
	m_buttonText.setFillColor(sf::Color::Black);
	m_buttonText.setCharacterSize(40u);

	m_nameText.setFont(m_twosonFont);
	m_nameText.setPosition(400.0f, 450.0f);
	m_nameText.setCharacterSize(30u);

	m_enterNameText.setFont(m_twosonFont);
	m_enterNameText.setPosition(400.0f, 350.0f);
	m_enterNameText.setString("ENTER YOUR NAME:");
	m_enterNameText.setOrigin(m_titleText.getGlobalBounds().width / 2, 0);

	m_helpText.setFont(m_twosonFont);
	m_helpText.setPosition(50.0f, 350.0f);
	m_helpText.setCharacterSize(20u);
	m_helpText.setLineSpacing(1.2f);

	std::string helpTextString = "";
	helpTextString.append("instructions:\nmovement:\nUSE THE ARROW KEYS TO MOVE AROUND\nTHE MAZE.");
	helpTextString.append("\ngoal:\nPICKUP ALL THE PELLETS IN THE LEVEL\nAND YOU WIN.\nTRY TO SURVIVE AS MANY LEVELS AS POSSIBLE\nAND GET THE HIGHEST SCORE.");
	helpTextString.append("\nghosts:\nTHE RED GHOSTS ARE EVIL DONT TOUCH\nTHEM OR YOU WILL LOSE A LIFE.\nLOSE ALL YOUR LIVES AND YOU LOSE.");
	m_helpText.setString(helpTextString);

	m_pauseText.setFont(m_twosonFont);
	m_pauseText.setPosition(310.0f, 350.0f);
	m_pauseText.setString("PAUSE");
	m_pauseText.setCharacterSize(40u);

	m_endText.setFont(m_twosonFont);
	m_endText.setPosition(240.0f, 10.0f);
	m_endText.setString("GAME OVER");
	m_endText.setCharacterSize(50u);

	m_scoreboardText.setFont(m_twosonFont);
	m_yourScoreText.setFont(m_twosonFont);
}

/// <summary>
/// Process the events for the screens.
/// </summary>
/// <param name="t_event">User event</param>
/// <param name="t_gameState">Game state</param>
/// <param name="t_playerName">Player's name</param>
/// <param name="t_gameOver">Game over bool</param>
void Screens::processEvents(sf::Event t_event, GameState & t_gameState, std::string & t_playerName, bool &t_gameOver, Player &t_player)
{
	switch (t_gameState)
	{
	case GameState::MenuScreen:
		menuEvents(t_event, t_gameState, t_gameOver, t_playerName);
		break;
	case GameState::NameScreen:
		nameScreenEvents(t_event, t_gameState, t_playerName);
		break;
	case GameState::HelpScreen:
		backButtonEvents(t_event, t_gameState);
		break;
	case GameState::CharacterScreen:
		characterScreenEvents(t_event, t_gameState, t_player);
		break;
	case GameState::GameOver:
		backButtonEvents(t_event, t_gameState);
		break;
	}
}

/// <summary>
/// Process the events for the menu screen.
/// </summary>
/// <param name="t_event">User event</param>
/// <param name="t_gameState">Game state</param>
/// <param name="t_gameOver">Game over bool</param>
void Screens::menuEvents(sf::Event t_event, GameState & t_gameState, bool & t_gameOver, std::string & t_playerName)
{
	if (sf::Event::MouseButtonPressed == t_event.type)
	{

		if (sf::Mouse::Left == t_event.mouseButton.button)
		{
			// Check that the click was within the horisontal bounds of the buttons
			if (t_event.mouseButton.x > BUTTON_ONE_POSITION.x - BUTTON_WIDTH / 2 && t_event.mouseButton.x < BUTTON_ONE_POSITION.x + BUTTON_WIDTH / 2)
			{
				// Check that the click is within the vertical bounds of the first the button (Start)
				if (t_event.mouseButton.y > BUTTON_ONE_POSITION.y - BUTTON_HEIGHT / 2 && t_event.mouseButton.y < BUTTON_ONE_POSITION.y + BUTTON_HEIGHT / 2)
				{
					t_gameState = GameState::NameScreen;
					m_characterNumber = 0;
					t_playerName = "";
				}
				// Check that the click is within the vertical bounds of the second the button (Help)
				if (t_event.mouseButton.y > BUTTON_TWO_POSITION.y - BUTTON_HEIGHT / 2 && t_event.mouseButton.y < BUTTON_TWO_POSITION.y + BUTTON_HEIGHT / 2)
				{
					t_gameState = GameState::HelpScreen;
				}
				// Check that the click is within the vertical bounds of the last the button (Exit)
				if (t_event.mouseButton.y > BUTTON_THREE_POSITION.y - BUTTON_HEIGHT / 2 && t_event.mouseButton.y < BUTTON_THREE_POSITION.y + BUTTON_HEIGHT / 2)
				{
					t_gameOver = true;;
				}
			}
		}
	}
}

/// <summary>
/// Process name screen events.
/// </summary>
/// <param name="t_event">User event</param>
/// <param name="t_gameState">Game state</param>
/// <param name="t_playerName">Player's name</param>
void Screens::nameScreenEvents(sf::Event t_event, GameState & t_gameState, std::string & t_playerName)
{
	if (t_event.type == sf::Event::TextEntered)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && t_playerName.length() > 0)
		{
			t_gameState = GameState::CharacterScreen;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) // Delete characters if backspace is pressed
		{
			if (t_playerName.length() > 0) // Check that there are characters in the array
			{
				t_playerName.pop_back(); // Remove the last letter of the string
			}
		}
		else if (t_playerName.length() < 5)
		{
			if (t_event.text.unicode >= 'a' && t_event.text.unicode <= 'z')
			{
				// Add the capital of the inputted letter onto the end player name string
				t_playerName.push_back(static_cast<char>(t_event.text.unicode - 32));
			}
			else if ((t_event.text.unicode >= 'A' && t_event.text.unicode <= 'Z') || t_event.text.unicode == ' ')
			{
				// Add the inputted letter onto the end player name string
				t_playerName.push_back(static_cast<char>(t_event.text.unicode));
			}

		}
	}
}

/// <summary>
/// Process the events for the help screen.
/// </summary>
/// <param name="t_event">User event</param>
/// <param name="t_gameState">Game state</param>
void Screens::backButtonEvents(sf::Event t_event, GameState & t_gameState)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Escape == t_event.key.code)
		{
			t_gameState = GameState::MenuScreen;
		}
	}
	if (sf::Event::MouseButtonPressed == t_event.type)
	{

		if (sf::Mouse::Left == t_event.mouseButton.button)
		{
			// Check that the click was within the horisontal bounds of the buttons
			if (t_event.mouseButton.x > BUTTON_BACK_POSITION.x - BUTTON_WIDTH / 2 && t_event.mouseButton.x < BUTTON_BACK_POSITION.x + BUTTON_WIDTH / 2)
			{
				// Check that the click is within the vertical bounds of the first the button (Start)
				if (t_event.mouseButton.y > BUTTON_BACK_POSITION.y - BUTTON_HEIGHT / 2 && t_event.mouseButton.y < BUTTON_BACK_POSITION.y + BUTTON_HEIGHT / 2)
				{
					t_gameState = GameState::MenuScreen;
				}
			}
		}
	}
}

/// <summary>
/// Process all user events for the character screen.
/// </summary>
/// <param name="t_event">User event</param>
/// <param name="t_gameState">Game state</param>
/// <param name="t_player">Player object</param>
void Screens::characterScreenEvents(sf::Event t_event, GameState & t_gameState, Player & t_player)
{
	t_player.setPosition({ static_cast<float>(WINDOW_WIDTH / 2 - CHAR_WIDTH), static_cast<float>(WINDOW_HEIGHT / 2) });
	t_player.setScale({ 2.0f,2.0f });

	t_player.setCharacter(m_characterNumber);

	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Right == t_event.key.code)
		{
			m_characterNumber++;
		}
		if (sf::Keyboard::Left == t_event.key.code)
		{
			m_characterNumber--;
		}
		if (sf::Keyboard::Enter == t_event.key.code)
		{
			t_player.setScale({ 1.0f,1.0f });
			t_player.refreshPosition();
			t_gameState = GameState::SetupGame;
		}
	}
}

/// <summary>
/// Draw function for all screens.
/// Draw the current screen.
/// </summary>
/// <param name="t_window">Game window</param>
/// <param name="t_gameState">Game state</param>
/// <param name="t_playerName">Player's name</param>
void Screens::draw(sf::RenderWindow & t_window, GameState t_gameState, std::string t_playerName, Player & t_player)
{
	t_window.draw(m_backgroundSprite);

	switch (t_gameState)
	{
	case GameState::MenuScreen:
		m_buttonText.setString("start");
		m_buttonText.setOrigin(static_cast<float>(m_buttonText.getGlobalBounds().width / 2), static_cast<float>(m_buttonText.getGlobalBounds().height));
		m_buttonText.setPosition(BUTTON_ONE_POSITION);
		m_buttonSprite.setPosition(BUTTON_ONE_POSITION);
		t_window.draw(m_buttonSprite);
		t_window.draw(m_buttonText);

		m_buttonText.setString("help");
		m_buttonText.setOrigin(static_cast<float>(m_buttonText.getGlobalBounds().width / 2), static_cast<float>(m_buttonText.getGlobalBounds().height));
		m_buttonText.setPosition(BUTTON_TWO_POSITION);
		m_buttonSprite.setPosition(BUTTON_TWO_POSITION);
		t_window.draw(m_buttonSprite);
		t_window.draw(m_buttonText);

		m_buttonText.setString("exit");
		m_buttonText.setOrigin(static_cast<float>(m_buttonText.getGlobalBounds().width / 2), static_cast<float>(m_buttonText.getGlobalBounds().height));
		m_buttonText.setPosition(BUTTON_THREE_POSITION);
		m_buttonSprite.setPosition(BUTTON_THREE_POSITION);
		t_window.draw(m_buttonSprite);
		t_window.draw(m_buttonText);
		break;
	case GameState::NameScreen:
		m_nameText.setString(t_playerName);
		m_nameText.setOrigin(static_cast<float>(m_nameText.getGlobalBounds().width / 2), static_cast<float>(m_nameText.getGlobalBounds().height / 1.5));
		t_window.draw(m_nameText);
		t_window.draw(m_enterNameText);
		break;
	case GameState::HelpScreen:
		m_buttonText.setString("back");
		m_buttonText.setOrigin(static_cast<float>(m_buttonText.getGlobalBounds().width / 2), static_cast<float>(m_buttonText.getGlobalBounds().height));
		m_buttonText.setPosition(BUTTON_BACK_POSITION);
		m_buttonSprite.setPosition(BUTTON_BACK_POSITION);
		t_window.draw(m_buttonSprite);
		t_window.draw(m_buttonText);
		t_window.draw(m_helpText);
		break;
	case GameState::CharacterScreen:
		m_arrowSprite.setScale(1.0f, 1.0f);
		m_arrowSprite.setPosition(static_cast<float>(WINDOW_WIDTH / 2 - 150), static_cast<float>(WINDOW_HEIGHT / 2));
		t_window.draw(m_arrowSprite);
		m_arrowSprite.setScale(-1.0f, 1.0f);
		m_arrowSprite.setPosition(static_cast<float>(WINDOW_WIDTH / 2 + 150), static_cast<float>(WINDOW_HEIGHT / 2));
		t_window.draw(m_arrowSprite);
		t_window.draw(t_player.getBody());
		break;
	}

	t_window.draw(m_titleText);
}

/// <summary>
/// Draw the pause text.
/// </summary>
/// <param name="t_window">Render window</param>
void Screens::drawPauseScreen(sf::RenderWindow &t_window)
{
	t_window.draw(m_pauseText);
}

/// <summary>
/// Draw the end screen text.
/// </summary>
/// <param name="t_window">Render window</param>
void Screens::drawEndScreen(sf::RenderWindow & t_window, std::string t_playerName, int t_playerScore, int t_playerCharNum, Player t_player)
{
	if (!m_gameOver)
	{
		saveScoreToFile(t_playerName, t_playerScore, t_playerCharNum);
		m_gameOver = true;
	}
	
	t_window.draw(m_endText);

	// Display the player's score
	t_player.setPosition({ YOUR_SCORE_POSITION.x, YOUR_SCORE_POSITION.y + 16 });
	t_player.setCharacter(t_playerCharNum);
	t_window.draw(t_player.getBody());

	m_scoreboardText.setFillColor(sf::Color::Blue);
	m_scoreboardText.setPosition(YOUR_SCORE_POSITION.x + 100, YOUR_SCORE_POSITION.y);
	m_scoreboardText.setString(t_playerName);
	t_window.draw(m_scoreboardText);
	m_scoreboardText.setPosition(YOUR_SCORE_POSITION.x + 250, YOUR_SCORE_POSITION.y);
	m_scoreboardText.setString(std::to_string(t_playerScore));
	t_window.draw(m_scoreboardText);
	m_scoreboardText.setFillColor(sf::Color::White);

	for (int i = 0; i < MAX_PLAYERS; i++) // Loop through all players in the scoreboard and display them
	{
		t_player.setPosition({ SCOREBOARD_POSITION.x, SCOREBOARD_POSITION.y + (i * 50) + 16 });
		t_player.setCharacter(m_characterNums[i]);
		t_window.draw(t_player.getBody());

		m_scoreboardText.setPosition(SCOREBOARD_POSITION.x + 50, SCOREBOARD_POSITION.y + (i * 50));
		m_scoreboardText.setString(std::to_string(i + 1));
		t_window.draw(m_scoreboardText);
		m_scoreboardText.setPosition(SCOREBOARD_POSITION.x + 100.0f, SCOREBOARD_POSITION.y + (i * 50));
		m_scoreboardText.setString(m_names[i]);
		t_window.draw(m_scoreboardText);
		m_scoreboardText.setPosition(SCOREBOARD_POSITION.x + 250.0f, SCOREBOARD_POSITION.y + (i * 50));
		m_scoreboardText.setString(std::to_string(m_scores[i]));
		t_window.draw(m_scoreboardText);
	}

	m_buttonText.setString("menu");
	m_buttonText.setOrigin(static_cast<float>(m_buttonText.getGlobalBounds().width / 2), static_cast<float>(m_buttonText.getGlobalBounds().height));
	m_buttonText.setPosition(BUTTON_BACK_POSITION);
	m_buttonSprite.setPosition(BUTTON_BACK_POSITION);
	t_window.draw(m_buttonSprite);
	t_window.draw(m_buttonText);
}

/// <summary>
/// Save the score to a file if it's within the top ten scores.
/// </summary>
void Screens::saveScoreToFile(std::string t_playerName, int t_playerScore, int t_playerCharNum)
{
	readScore(); // Read in data from the scoreboard file
	addScore(t_playerName, t_playerScore, t_playerCharNum); // Add the player score to the arrays if the score fits in the top 10
	writeScore(); // Write the arrays back to the file
}

/// <summary>
/// Read from the player scores file and save the data to a set of arrays.
/// </summary>
/// <param name="t_names">Names array</param>
/// <param name="t_scores">Scores array</param>
/// <param name="t_characterNums">Character number array</param>
void Screens::readScore()
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
						m_names[lineNum] = item;
					}
					else if (dataNum == 1) // Scores
					{
						m_scores[lineNum] = std::stoi(item);
					}
					else if (dataNum == 2) // Character number
					{
						m_characterNums[lineNum] = std::stoi(item);
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
void Screens::addScore(std::string t_playerName, int t_playerScore, int t_playerCharNum)
{
	for (int i = 0; i < MAX_PLAYERS; i++) // Loop through the player data arrays
	{
		if (t_playerScore > m_scores[i]) // If the player score is greater than the current score
		{
			for (int j = MAX_PLAYERS - 1; j > i; j--) // Loop backwards through the array to move all items back
			{
				m_names[j] = m_names[j - 1]; // Move the name back one cell
				m_scores[j] = m_scores[j - 1]; // Move the score back one cell
				m_characterNums[j] = m_characterNums[j - 1]; // Move the character number
			}
			m_names[i] = t_playerName; // Set the player name to the cell
			m_scores[i] = t_playerScore; // Set the player score to the cell
			m_characterNums[i] = t_playerCharNum; // Set the player character number to the cell
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
void Screens::writeScore()
{
	std::ofstream outputFile; // Create an output file pointer
	outputFile.open("DATA//scoreboard.txt"); // Open the file

	if (outputFile.is_open()) // Check the file is open
	{
		for (int i = 0; i < MAX_PLAYERS; i++) // Loop through the player data array
		{
			if (m_names[i] == "") // Check if the cell is blank
			{
				break; // Break if the name is blank
			}
			outputFile << m_names[i] << ","; // Write the current name to the file
			outputFile << m_scores[i] << ","; // Write the current score to the file
			outputFile << m_characterNums[i] << ","; // Write the current character number to a file
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