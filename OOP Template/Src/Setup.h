#pragma once

namespace WINDOW {
	const int WIDTH = 1400;
	const int HEIGHT = 1000;
}

struct NODE {
	static float G;
};

struct GRID {
	static bool GRIDSIZE_CHANGED;
	static unsigned int GRIDSIZE;

	static bool RANDOM_WALLS;
	static bool RANDOM_START;
	static bool RANDOM_END;
	static unsigned int RANDOM_WALLS_CHANCE;

	static unsigned int WIDTH;
	static unsigned int HEIGHT;
	static int X;
	static int Y;

	static bool AUTORESET;
	static bool RESET;
};