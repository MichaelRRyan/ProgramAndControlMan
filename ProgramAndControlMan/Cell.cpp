/// @Author Michael Rainsford Ryan
#include "Cell.h"

Cell::Cell()
{
	m_containsWall = false;
	m_containsCoin = false;
	loadFiles();
}

void Cell::setContainsWall(bool t_wall)
{
	m_containsWall = t_wall;
	if (t_wall)
	{
		m_texturePosition = sf::IntRect{ TILE_SIZE * 10,TILE_SIZE * 7,TILE_SIZE,TILE_SIZE };
	}
}

void Cell::setContainsCoin(bool t_coin)
{
	m_containsCoin = t_coin;
	if (t_coin)
	{
		m_texturePosition = sf::IntRect{ TILE_SIZE * 12,TILE_SIZE * 24,TILE_SIZE,TILE_SIZE };
	}
}
