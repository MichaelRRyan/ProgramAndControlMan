#include "Screens.h"



Screens::Screens()
{
	loadFiles();
}

void Screens::loadFiles()
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\pacmanSprite.png"))
	{
		// Error loading background sprite
	}
	if (!m_buttonTexture.loadFromFile("ASSETS\\IMAGES\\yellowSheet.png"))
	{
		// Error loading background sprite
	}
}

void Screens::processEvents(sf::Event t_event)
{
}

void Screens::draw(sf::RenderWindow t_window)
{
}

