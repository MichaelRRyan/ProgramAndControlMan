/// @Author Michael Rainsford Ryan

#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 800u, 800u, 32u }, "Basic Game" },
	m_exitGame{ false }
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
		m_player.move(checkMovementInput(nextEvent), m_maze);
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	m_scoreText.setString("Score: " + std::to_string(m_player.getScore()));
	m_ghost.move(m_maze);
}

void Game::render()
{
	m_window.clear();

	drawMaze();
	m_window.draw(m_player.getBody());
	m_window.draw(m_scoreText);
	m_window.draw(m_ghost.getBody());

	m_window.display();
}

void Game::setupGame()
{
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

				m_ghost.setPos(row, col);
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
	if (t_nextEvent.type == sf::Event::KeyPressed)
	{
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

	return Direction::None;
}
