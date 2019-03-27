/// @Author Michael Rainsford Ryan

#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32u }, "Program And Control Man" },
	m_exitGame{ false },
	m_gameState{ GameState::MenuScreen }
{
	if (!m_terrainTexture.loadFromFile("ASSETS\\IMAGES\\terrain_atlas.png"))
	{
		// Error loading file
	}
	m_tileSprite.setTexture(m_terrainTexture);

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
		if (m_gameState == GameState::MenuScreen || m_gameState == GameState::HelpScreen
			|| m_gameState == GameState::NameScreen || m_gameState == GameState::CharacterScreen)
		{
			m_menuScreens.processEvents(nextEvent, m_gameState, m_playerName, m_exitGame, m_player);
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
			m_player.checkCollision(m_ghosts[i]);
			m_ghosts[i].move(m_maze, m_ghosts);
		}

		m_scoreText.setString(m_playerName + "'s Score: " + std::to_string(m_player.getScore()));
		m_livesText.setString("Health: " + std::to_string(m_player.getLives()));

		m_player.update(m_maze, m_gameState);
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
			m_window.draw(m_ghosts[i].getBody());
		}

		m_window.draw(m_scoreText);
		m_window.draw(m_livesText);
		break;
	case GameState::Pause:
		break;
	case GameState::GameOver:
		m_window.draw(m_gameOverText);
		m_window.draw(m_scoreText);
		break;
	default:
		m_menuScreens.draw(m_window, m_gameState, m_playerName, m_player);
		break;
	}

	m_window.display();
}

void Game::setupGame()
{
	m_player.setScore(0);
	m_player.setLives(3);

	bool found = false; // Whether the player has been placed or not
	int ghosts = 0;
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			if (m_maze[row][col].getTileType() != Tile::Rock)
			{
				if (!found)
				{
					m_player.setPos({ col, row });
					m_maze[row][col].setTileType(Tile::None);
					found = true;
				}
			}
		}
	}

	// Loop backwards through the maze to place the ghosts
	for (int row = MAX_ROWS - 1; row >= 0; row--)
	{
		for (int col = MAX_COLS - 1; col  >= 0; col--)
		{
			if (ghosts < MAX_GHOSTS)
			{
				if (m_maze[row][col].getTileType() != Tile::Rock)
				{
					m_ghosts[ghosts].setPos(row, col);
					ghosts++;
				}
			}
			else
			{
				break;
			}
		}
		if (ghosts >= MAX_GHOSTS)
		{
			break;
		}
	}
}

void Game::setupMaze()
{
	int mazeSetup[MAX_ROWS][MAX_COLS]{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0 },
	{ 0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0 },
	{ 0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,1,0,0,1,1,0,1,1,0,0 },
	{ 0,0,0,0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0 },
	{ 0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,1,0,0,0,0,0,1,1,1,0 },
	{ 0,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,1,1,0 },
	{ 0,0,0,0,0,1,0,0,1,1,1,1,1,3,1,3,1,0,0,1,0,0,0,0,0 },
	{ 0,0,1,1,0,1,0,0,1,1,1,1,0,0,0,0,1,0,0,1,0,1,1,0,0 },
	{ 0,0,1,1,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0 },
	{ 0,0,1,1,0,1,0,0,1,1,0,1,1,1,0,0,0,0,0,1,0,1,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,1,0,0 },
	{ 0,0,1,1,0,1,0,0,0,0,1,1,1,0,0,1,1,0,0,1,0,1,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,0,1,0,0,1,0,0,0,0,1,1,1,1,0,0,1,0,1,1,0,0 },
	{ 0,0,1,1,0,1,0,0,1,3,1,3,1,1,1,1,1,0,0,1,0,1,1,0,0 },
	{ 0,0,1,1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,1,1,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,3,1,1,1,0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,1,1,1,3,0 },
	{ 0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,0,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0 },
	{ 0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0 },
	{ 0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};

	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			m_maze[row][col].setTileType(static_cast<Tile>(mazeSetup[row][col]));

			if (mazeSetup[row][col] == 0) // Set coins to any empty spots in the maze
			{
				m_maze[row][col].setTileType(Tile::Coin);
			}

			if (row == 0 || row == MAX_ROWS - 1 || col == 0 || col == MAX_COLS - 1) // Setup the sides of the maze so that it always has borders
			{
				m_maze[row][col].setTileType(Tile::Rock);
			}
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
	m_livesText.setFont(m_arialFont);
	m_livesText.setPosition(WINDOW_WIDTH / 2, 0.0f);

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
			m_tileSprite.setPosition(static_cast<float>(32 * col), static_cast<float>(32 * row)); // Set the x and y of the tile sprite
			int grassType = (col + row) % 3; // Picks between grass tiles to draw for each tile based off the row and col
			m_tileSprite.setTextureRect(sf::IntRect{ TILE_SIZE * (21 + grassType), TILE_SIZE * 5, TILE_SIZE, TILE_SIZE }); // Set the ground tile
			m_window.draw(m_tileSprite); // Draw the ground

			if (m_maze[row][col].getTileType() != Tile::None) // Draw a rock or coin if the cell contains one
			{
				m_tileSprite.setTextureRect(m_maze[row][col].getTexturePosition()); // Set the sprite to the cell type
				m_window.draw(m_tileSprite); // Draw the cell
			}
		}
	}
}
