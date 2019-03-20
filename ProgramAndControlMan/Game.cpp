/// @Author Michael Rainsford Ryan

#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 800u, 800u, 32u }, "Basic Game" },
	m_exitGame{ false },
	m_gameState{ GameState::MenuScreen }
{
	setupMaze();
	setupGame();
	setupFontAndText();
}

Game::~Game()
{

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // Run as many times as possible
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // Run at a minimum of 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // Run as many times as possible
	}
}

void Game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type) // check if the close window button is clicked on.
		{
			m_window.close();
		}
		if (m_gameState == GameState::Gameplay)
		{
			m_player.move(checkMovementInput(nextEvent), m_maze);
		}
		if (m_gameState == GameState::GameOver)
		{
			if (sf::Event::KeyPressed == nextEvent.type)
			{
				if (sf::Keyboard::R == nextEvent.key.code)
				{
					setupMaze();
					setupGame();
					m_gameState = GameState::Gameplay;
				}
			}
		}
		if (m_gameState == GameState::MenuScreen || m_gameState == GameState::HelpScreen || m_gameState == GameState::NameScreen)
		{
			m_menuScreens.processEvents(nextEvent, m_gameState, m_playerName);
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (m_gameState == GameState::Gameplay)
	{
		for (int i = 0; i < MAX_GHOSTS; i++)
		{
			if (m_player.getPos() == m_ghost[i].getPos()) // Check if the row and col of a ghost and the player match
			{
				m_gameState = GameState::GameOver;
			}
		}

		m_scoreText.setString(m_playerName + "'s Score: " + std::to_string(m_player.getScore()));

		for (int i = 0; i < MAX_GHOSTS; i++)
		{
			m_ghost[i].move(m_maze);
		}
	}
	
}

void Game::render()
{
	m_window.clear();

	switch (m_gameState)
	{
	case GameState::Gameplay:
		drawMaze();
		m_window.draw(m_player.getBody());

		for (int i = 0; i < MAX_GHOSTS; i++)
		{
			m_window.draw(m_ghost[i].getBody());
		}

		m_window.draw(m_scoreText);
		break;
	case GameState::Pause:
		break;
	case GameState::GameOver:
		m_window.draw(m_gameOverText);
		break;
	default:
		m_menuScreens.draw(m_window, m_gameState, m_playerName);
		break;
	}

	m_window.display();
}

void Game::setupGame()
{
	m_player.setScore(0);

	bool found = false;
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			if (!m_maze[row][col].getContainsWall())
			{
				if (!found)
				{
					m_player.setPos({ col, row });
					m_maze[row][col].setContainsCoin(false);
					found = true;
				}

				for (int i = 0; i < MAX_GHOSTS; i++)
				{
					m_ghost[i].setPos(row, col);
				}
			}
		}
	}
}

void Game::setupMaze()
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			// Reset all values before setting them
			m_maze[row][col].setContainsCoin(false);
			m_maze[row][col].setContainsWall(false);

			if (rand() % 5 == 0)
			{
				m_maze[row][col].setContainsWall(true);
			}
			else if (row == 0 || row == MAX_ROWS - 1 || col == 0 || col == MAX_COLS - 1)
			{
				m_maze[row][col].setContainsWall(true);
			}
			else
			{
				m_maze[row][col].setContainsCoin(true);
			}
			m_maze[row][col].setPosition({ 32.0f * col, 32.0f * row }); // Sets the position based on the row and column
		}
	}
}

void Game::setupFontAndText()
{
	if (!m_arialFont.loadFromFile("ASSETS\\FONTS\\arial.ttf"))
	{
		// Error loading font file
	}
	m_scoreText.setFont(m_arialFont);

	// Setup the game over text
	m_gameOverText.setFont(m_arialFont);
	m_gameOverText.setString("GAME OVER");
	m_gameOverText.setCharacterSize(50u);
	m_gameOverText.setOrigin(m_gameOverText.getGlobalBounds().width / 2, m_gameOverText.getGlobalBounds().height / 2);
	m_gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void Game::drawMaze()
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			if (m_maze[row][col].getContainsCoin() || m_maze[row][col].getContainsWall())
			{
				m_window.draw(m_maze[row][col].getBody());
			}
		}
	}
}

Direction Game::checkMovementInput(sf::Event t_nextEvent)
{
	if (m_player.getCanMove()) // Check that the player can move
	{
		if (t_nextEvent.type == sf::Event::KeyPressed) // Check if a key is pressed
		{
			m_player.setCanMove(false); // Player can no longer move

			// Get and return the player move direction
			if (t_nextEvent.key.code == sf::Keyboard::Left)
			{
				return Direction::West;
			}
			if (t_nextEvent.key.code == sf::Keyboard::Right)
			{
				return Direction::East;
			}
			if (t_nextEvent.key.code == sf::Keyboard::Left)
			{
				return Direction::West;
			}
			if (t_nextEvent.key.code == sf::Keyboard::Up)
			{
				return Direction::North;
			}
			if (t_nextEvent.key.code == sf::Keyboard::Down)
			{
				return Direction::South;
			}
		}
	}
	else // If the player can't move
	{
		if (t_nextEvent.type == sf::Event::KeyReleased) // If a key was released
		{
			m_player.setCanMove(true); // The player can move again
		}
	}

	return Direction::None;
}
