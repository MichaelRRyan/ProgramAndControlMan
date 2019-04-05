/// @Author Michael Rainsford Ryan
#include "Cell.h"

Cell::Cell()
{
	m_tileType = Tile::None; // Set the initial tile type to nothing
}

void Cell::setTileType(Tile t_tileType)
{
	m_tileType = t_tileType; // Set the functioning cell type

	switch (t_tileType) // Set the current texture
	{
	case Tile::None:
		break;
	case Tile::Rock:
		m_texturePosition = sf::IntRect{ TILE_SIZE * 10,TILE_SIZE * 7,TILE_SIZE,TILE_SIZE }; // Set a red rock texture
		break;
	case Tile::Coin:
		m_texturePosition = sf::IntRect{ TILE_SIZE * 12,TILE_SIZE * 24,TILE_SIZE,TILE_SIZE }; // Set a berry texture
		break;
	case Tile::Moveable:
		m_texturePosition = sf::IntRect{ TILE_SIZE * 15,TILE_SIZE * 15,TILE_SIZE,TILE_SIZE }; // Set a white rock texture
		break;
	}
}
