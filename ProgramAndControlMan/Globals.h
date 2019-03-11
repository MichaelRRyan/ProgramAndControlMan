/// @Author Michael Rainsford Ryan
#pragma once

enum class Direction
{
	None,
	North,
	South,
	West,
	East
};

static const int MAX_ROWS{ 25 };
static const int MAX_COLS{ 25 };

static const unsigned WINDOW_WIDTH{ 800u };
static const unsigned WINDOW_HEIGHT{ 800u };