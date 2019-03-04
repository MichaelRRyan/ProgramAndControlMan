/// @Author Michael Rainsford Ryan

#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 800u, 800u, 32u }, "Basic Game" },
	m_exitGame{ false }
{
	setupMaze();
	setupGame();
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
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

void Game::render()
{
	m_window.clear();

	drawMaze();

	m_window.display();
}

void Game::setupGame()
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			if (!m_maze[row][col].getContainsWall())
			{
				m_player.setPos({ row, col });
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
			else
			{
				m_maze[row][col].setContainsCoin(true);
			}
			m_maze[row][col].setPosition({ 32.0f * row, 32.0f * col }); // Sets the position based on the row and column
		}
	}
}

void Game::drawMaze()
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			m_window.draw(m_maze[row][col].getBody());
		}
	}
	m_window.draw(m_player.getBody());
}