/// @Author Michael Rainsford Ryan
#include "Cell.h"

Cell::Cell()
{
	loadFiles();
	containsWall = false;
	containsCoin = false;
	body.setTexture(blankTexture);
}

void Cell::loadFiles()
{
	if (!wallTexture.loadFromFile("ASSETS\\IMAGES\\wallCell.jpg"))
	{
		// Error
	}
	if (!coinTexture.loadFromFile("ASSETS\\IMAGES\\bigPill.png"))
	{
		// Error
	}
	if (!blankTexture.loadFromFile("ASSETS\\IMAGES\\emptyCell.png"))
	{
		// Error
	}
}

void Cell::setContainsWall(bool t_wall)
{
	containsWall = t_wall;
	if (t_wall)
	{
		body.setTexture(wallTexture);
	}
}

void Cell::setContainsCoin(bool t_coin)
{
	containsCoin = t_coin;
	if (t_coin)
	{
		body.setTexture(coinTexture);
	}
}
