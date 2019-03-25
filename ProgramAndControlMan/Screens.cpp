#include "Screens.h"


/// <summary>
/// Default constructer and setup for the game screens.
/// </summary>
Screens::Screens()
{
	loadFiles();

	m_backgroundSprite.setTexture(m_backgroundTexture);

	m_buttonSprite.setTexture(m_buttonTexture);
	m_buttonSprite.setTextureRect(sf::IntRect{ BUTTON_IMAGE_WIDTH,45,BUTTON_IMAGE_WIDTH,BUTTON_IMAGE_HEIGHT });
	m_buttonSprite.setOrigin(BUTTON_IMAGE_WIDTH / 2, BUTTON_IMAGE_HEIGHT / 2);
	m_buttonSprite.setScale(1.8f, 1.8f);

	m_titleText.setFont(m_pacFont);
	m_titleText.setCharacterSize(80u);
	m_titleText.setString("PACMAN");
	m_titleText.setPosition(400.0f, 80.0f);
	m_titleText.setOrigin(m_titleText.getGlobalBounds().width / 2, 0);

	m_buttonText.setFont(m_pacFont);
	m_buttonText.setFillColor(sf::Color::Black);
	m_buttonText.setCharacterSize(40u);

	m_nameText.setFont(m_pacFont);
	m_nameText.setFillColor(sf::Color::White);
	m_nameText.setPosition(400.0f, 450.0f);
	m_nameText.setCharacterSize(30u);

	m_enterNameText.setFont(m_pacFont);
	m_enterNameText.setFillColor(sf::Color::White);
	m_enterNameText.setPosition(400.0f, 350.0f);
	m_enterNameText.setCharacterSize(30u);
	m_enterNameText.setString("ENTER YOUR NAME:");
	m_enterNameText.setOrigin(m_titleText.getGlobalBounds().width / 2, 0);
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
	if (!m_pacFont.loadFromFile("ASSETS\\FONTS\\pac_font.ttf"))
	{
		// Error loading font file
	}
}

/// <summary>
/// Process the events for the screens.
/// </summary>
/// <param name="t_event">User event</param>
/// <param name="t_gameState">Game state</param>
/// <param name="t_playerName">Player's name</param>
/// <param name="t_gameOver">Game over bool</param>
void Screens::processEvents(sf::Event t_event, GameState & t_gameState, std::string & t_playerName, bool &t_gameOver)
{
	switch (t_gameState)
	{
	case GameState::MenuScreen:
		menuEvents(t_event, t_gameState, t_gameOver);
		break;
	case GameState::NameScreen:
		nameScreenEvents(t_event, t_gameState, t_playerName);
		break;
	case GameState::HelpScreen:
		helpScreenEvents(t_event, t_gameState);
		break;
	}
}

/// <summary>
/// Process the events for the menu screen.
/// </summary>
/// <param name="t_event">User event</param>
/// <param name="t_gameState">Game state</param>
/// <param name="t_gameOver">Game over bool</param>
void Screens::menuEvents(sf::Event t_event, GameState & t_gameState, bool & t_gameOver)
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
			t_gameState = GameState::Gameplay;
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
void Screens::helpScreenEvents(sf::Event t_event, GameState & t_gameState)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Escape == t_event.key.code)
		{
			t_gameState = GameState::MenuScreen;
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
void Screens::draw(sf::RenderWindow & t_window, GameState t_gameState, std::string t_playerName)
{
	t_window.draw(m_backgroundSprite);

	switch (t_gameState)
	{
	case GameState::MenuScreen:
		m_buttonText.setString("start");
		m_buttonText.setOrigin(m_buttonText.getGlobalBounds().width / 2, m_buttonText.getGlobalBounds().height / 1.5);
		m_buttonText.setPosition(BUTTON_ONE_POSITION);
		m_buttonSprite.setPosition(BUTTON_ONE_POSITION);
		t_window.draw(m_buttonSprite);
		t_window.draw(m_buttonText);

		m_buttonText.setString("help");
		m_buttonText.setOrigin(m_buttonText.getGlobalBounds().width / 2, m_buttonText.getGlobalBounds().height / 1.5);
		m_buttonText.setPosition(BUTTON_TWO_POSITION);
		m_buttonSprite.setPosition(BUTTON_TWO_POSITION);
		t_window.draw(m_buttonSprite);
		t_window.draw(m_buttonText);

		m_buttonText.setString("exit");
		m_buttonText.setOrigin(m_buttonText.getGlobalBounds().width / 2, m_buttonText.getGlobalBounds().height / 1.5);
		m_buttonText.setPosition(BUTTON_THREE_POSITION);
		m_buttonSprite.setPosition(BUTTON_THREE_POSITION);
		t_window.draw(m_buttonSprite);
		t_window.draw(m_buttonText);
		break;
	case GameState::NameScreen:
		m_nameText.setString(t_playerName);
		m_nameText.setOrigin(m_nameText.getGlobalBounds().width / 2, m_nameText.getGlobalBounds().height / 1.5);
		t_window.draw(m_nameText);
		t_window.draw(m_enterNameText);
		break;
	}

	

	t_window.draw(m_titleText);
}

