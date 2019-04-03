/// -----------------------------------
/// The second project for programming.
/// A PacMan style game with Legend of
/// Zelda inspired gameplay. 
/// -----------------------------------
/// @Author Michael Rainsford Ryan
/// @Date 04/03/2019
/// Estimated time to finish: 30h
/// Aprox time taken: 25h 
/// -----------------------------------
/// Issues/To-Do:
/// - Character sprite moves to the left when game is over and reset once (Origin not reset)
/// - Help screen needs to be filled out
/// - Scoreboard button needed on main menu
/// - Menu needs to be redone

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif

#include "Game.h"
#include <ctime>
#include <cstdlib>

int main()
{
	srand(static_cast<unsigned>(time(nullptr))); // Set the random value seed

	Game game; // Create a game class
	game.run(); // Run the game class

	return EXIT_SUCCESS;
}
