#pragma once
#include "SDL.h"
#include "../includes.h"

struct Rect;
class Grid {
public:
	Grid(int size);

	void update();
	void render();
	void renderGrid();
	void sizeTo(int size);
	void color(int r, int g, int b);

	std::vector<std::vector<int>> grid;
private:
	SDL_Texture* targetTex;
	SDL_Color gridColor;
	Rect* rect; // renders grid in this area
	int gridSize;
	bool sizeChanged = false;
};
