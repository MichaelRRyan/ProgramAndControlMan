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

/// <summary>
/// <para>Manage the framerate for the game.</para>
/// <para>Calls the processEvents, update, and render function in their respective time.</para>
/// </summary>
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

/// <summary>
/// <para>Process all user events for the game.</para>
/// <para>Manages restarting the game if the user
/// presses 'R' once the game is over</para>
/// <para>Calls the menu screen to manage the screens.</para>
/// </summary>
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
					m_playerName = "";
					m_gameState = GameState::MenuScreen;
				}
			}
		}
		if (m_gameState == GameState::MenuScreen || m_gameState == GameState::HelpScreen
			|| m_gameState == GameState::NameScreen || m_gameState == GameState::CharacterScreen)
		{
			m_menuScreens.processEvents(nextEvent, m_gameState, m_playerName, m_exitGame, m_player);
		}
		if (sf::Event::KeyPressed == nextEvent.type)
		{
			if (sf::Keyboard::Comma == nextEvent.key.code)
			{
				m_menuScreens.saveScoreToFile(m_playerName, m_player.getScore(), m_player.getCharNum());
			}
		}
	}
}

/// <summary>
/// <para>Update the game world.</para>
/// <para>Checks if exitGame bool is true and closes window.</para>
/// <para>Updates the enemies and player and checks their collisions.</para>
/// <para>Updates the score and health text.</para>
/// </summary>
/// <param name="t_deltaTime">Time per frame</param>
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
			m_ghosts[i].move(m_maze, m_ghosts, m_player);
		}

		m_scoreText.setString(m_playerName + "'s Score: " + std::to_string(m_player.getScore()));
		m_livesText.setString("Health: " + std::to_string(m_player.getLives()));

		m_player.update(m_maze, m_gameState);
	}
}

/// <summary>
/// <para>Draws all game objects.</para>
/// <para>Draws each game object according to the game state.</para>
/// </summary>
void Game::render()
{
	m_window.clear();

	switch (m_gameState)
	{
	case GameState::Gameplay:
		drawMaze();

		// Loop through all rows to draw players and enemies in order of screen height
		for (int row = 0; row < MAX_ROWS; row++)
		{
			for (int i = 0; i < MAX_GHOSTS; i++) // Loop through all the ghosts
			{
				if (m_ghosts[i].getPos().y == row) // Check if the ghost is on this row
				{
					m_window.draw(m_ghosts[i].getBody());
				}
			}

			if (m_player.getPos().y == row) // Check if the player is on this row
			{
				m_window.draw(m_player.getBody());
			}
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

/// <summary>
/// <para>Sets up the game objects.</para>
/// <para>Sets up the player and enemies.</para>
/// </summary>
void Game::setupGame()
{
	m_player.respawn();
	m_maze[2][12].setTileType(Tile::None);

	m_ghosts[0].setPos(4, 4); // Set the enemy to the top left corner of the maze
	m_ghosts[1].setPos(MAX_COLS - 5, 4); // Set the enemy to the top right corner of the maze
	m_ghosts[2].setPos(4, MAX_ROWS - 4); // Set the enemy to the bottom left of the maze
	m_ghosts[3].setPos(MAX_COLS - 5, MAX_ROWS - 5); // Set the enemy to botton right of the maze
}

/// <summary>
/// <para>Setup the maze array with a temporary maze.</para>
/// </summary>
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

/// <summary>
/// <para>Loads the font file and sets up the text objects.</para>
/// </summary>
void Game::setupFontAndText()
{
	if (!m_arialFont.loadFromFile("ASSETS\\FONTS\\arial.ttf"))
	{
		// Error loading font file
	}
	m_scoreText.setFont(m_arialFont);
	m_scoreText.setPosition(0.0f, static_cast<float>(WINDOW_HEIGHT - 45));
	m_livesText.setFont(m_arialFont);
	m_livesText.setPosition(static_cast<float>(WINDOW_WIDTH / 2 + 50), static_cast<float>(WINDOW_HEIGHT - 45));

	// Setup the game over text
	m_gameOverText.setFont(m_arialFont);
	m_gameOverText.setString("GAME OVER");
	m_gameOverText.setCharacterSize(50u);
	m_gameOverText.setOrigin(m_gameOverText.getGlobalBounds().width / 2, m_gameOverText.getGlobalBounds().height / 2);
	m_gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

/// <summary>
/// <para>Draws each cell of the maze and the background.</para>
/// </summary>
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
