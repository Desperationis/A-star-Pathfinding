#pragma once
#include "SDL.h"
#include "../includes.h"

struct Rect;
class Grid {
public:
	Grid(int size);
	~Grid();

	void update();
	void render();
	void renderGrid();
	void load();
	void sizeTo(int size);
	void color(int r, int g, int b);

	std::vector<std::vector<int>> grid;
	SDL_Texture* targetTex;
private:
	SDL_Color gridColor;
	Rect* rect; // renders grid in this area
	int gridSize;
	bool sizeChanged = false;
};
