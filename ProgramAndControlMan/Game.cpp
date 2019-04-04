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

	if (!m_hudIconsTexure.loadFromFile("ASSETS\\IMAGES\\hud_icons.png"))
	{
		// Error loading file
	}
	m_hudIcons.setTexture(m_hudIconsTexure);

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

		switch (m_gameState) // Process events for each game state
		{
		case GameState::Gameplay:
			if (sf::Event::KeyPressed == nextEvent.type)
			{
				if (sf::Keyboard::P == nextEvent.key.code)
				{
					m_gameState = GameState::Pause;
				}
			}
			break;
		case GameState::Pause:
			if (sf::Event::KeyPressed == nextEvent.type)
			{
				if (sf::Keyboard::Escape == nextEvent.key.code)
				{
					m_gameState = GameState::Gameplay;
				}
			}
			break;
		default:
			m_menuScreens.processEvents(nextEvent, m_gameState, m_playerName, m_exitGame, m_player);
			break;
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
		for (int i = 0; i < MAX_GHOSTS; i++) // Loop through all ghosts
		{
			m_player.checkCollision(m_ghosts[i]); // Check collisions with the player and ghosts
			m_ghosts[i].move(m_maze, m_ghosts, m_player); // Move the ghosts
		}

		m_scoreText.setString(std::to_string(m_player.getScore())); // Update the score text
		m_livesText.setString(std::to_string(m_player.getLives())); // Update the health text

		m_player.update(m_maze, m_gameState); // Update the player
	}
	else if (m_gameState == GameState::SetupGame)
	{
		setupGame(); // Setup the game objects
		m_gameState = GameState::Gameplay; // Switch to gameplay state
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
		drawGameplay(); // Draw the gameplay objects
		break;
	case GameState::Pause:
		drawGameplay(); // Draw the gameplay objects
		m_menuScreens.drawPauseScreen(m_window); // Draw the pause screen
		break;
	case GameState::GameOver:
		m_menuScreens.drawEndScreen(m_window, m_playerName, m_player.getScore(), m_player.getCharNum(), m_player); // Draw the end screen
		break;
	default:
		m_menuScreens.draw(m_window, m_gameState, m_playerName, m_player); // Draw the menu screen
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
	setupMaze();
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
	int mazeSetup[MAX_ROWS][MAX_COLS]{ // Setup a temporary 2D maze to setup the main maze
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

	for (int row = 0; row < MAX_ROWS; row++) // Loop through rows
	{
		for (int col = 0; col < MAX_COLS; col++) // Loops through columns
		{
			m_maze[row][col].setTileType(static_cast<Tile>(mazeSetup[row][col])); // Set the type of the tile

			if (mazeSetup[row][col] == 0) // Set coins to any empty spots in the maze
			{
				m_maze[row][col].setTileType(Tile::Coin); // Set a coin to any blank cell
			}

			if (row == 0 || row == MAX_ROWS - 1 || col == 0 || col == MAX_COLS - 1) // Setup the sides of the maze so that it always has borders
			{
				m_maze[row][col].setTileType(Tile::Rock); // Set walls at each edge
			}
		}
	}
}

/// <summary>
/// <para>Loads the font file and sets up the text objects.</para>
/// </summary>
void Game::setupFontAndText()
{
	if (!m_twosonFont.loadFromFile("ASSETS\\FONTS\\twoson.ttf"))
	{
		// Error loading font file
	}
	m_scoreText.setFont(m_twosonFont);
	m_scoreText.setPosition(static_cast<float>(WINDOW_WIDTH / 2 + 70), 0.0f);

	m_livesText.setFont(m_twosonFont);
	m_livesText.setPosition(static_cast<float>(WINDOW_WIDTH / 2 - 60), 0.0f);

	// Setup the game over text
	m_gameOverText.setFont(m_twosonFont);
	m_gameOverText.setString("GAME OVER");
	m_gameOverText.setCharacterSize(50u);
	m_gameOverText.setOrigin(m_gameOverText.getGlobalBounds().width / 2, m_gameOverText.getGlobalBounds().height / 2);
	m_gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

/// <summary>
/// <para>Draws each cell of the maze and the background.</para>
/// <para>Draw the player and each enemy in order of screen height.</para>
/// <para>Draw the hud with health and score.</para>
/// </summary>
void Game::drawGameplay()
{
	for (int row = 0; row < MAX_ROWS; row++) // Loop rows
	{
		for (int col = 0; col < MAX_COLS; col++) // Loop columns
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

	// Set the text and hud icon positions and draw
	m_hudIcons.setTextureRect({ 64, 0, 288, 32 });
	m_hudIcons.setPosition(256.0f, 0.0f);
	m_window.draw(m_hudIcons);

	m_hudIcons.setTextureRect({ 0, 0, 32, 32 });
	m_hudIcons.setPosition(static_cast<float>(WINDOW_WIDTH / 2 - 100), 0.0f);
	m_window.draw(m_hudIcons);
	
	m_hudIcons.setTextureRect({ 32, 0, 32, 32 });
	m_hudIcons.setPosition(static_cast<float>(WINDOW_WIDTH / 2 + 20), 0.0f);
	m_window.draw(m_hudIcons);
	
	m_window.draw(m_scoreText);
	m_window.draw(m_livesText);
}
