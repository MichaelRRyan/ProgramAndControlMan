/// @Author Michael Rainsford Ryan
#include "Cell.h"

Cell::Cell()
{
	m_tileType = Tile::None;
}

void Cell::setTileType(Tile t_tileType)
{
	m_tileType = t_tileType;

	switch (t_tileType)
	{
	case Tile::None:
		break;
	case Tile::Rock:
		m_texturePosition = sf::IntRect{ TILE_SIZE * 10,TILE_SIZE * 7,TILE_SIZE,TILE_SIZE };
		break;
	case Tile::Coin:
		m_texturePosition = sf::IntRect{ TILE_SIZE * 12,TILE_SIZE * 24,TILE_SIZE,TILE_SIZE };
		break;
	}
}
