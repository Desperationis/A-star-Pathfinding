#include "Grid.h"
#include "../Tools/TM.h"
#include "../Tools/InputSystem.h"
#include "../Setup.h"
#include "../Tools/Rect.h"


Grid::Grid(int size) {
	sizeTo(size);
	gridColor = SDL_Color{ 0,0,0,100 };
	GRID::Y = (WINDOW::HEIGHT / 2) - (GRID::WIDTH / 2);
	rect = new Rect(GRID::X, GRID::Y, GRID::WIDTH, GRID::HEIGHT); // width and height MUST stay the same
	targetTex = nullptr;
}

Grid::~Grid() {
	SDL_DestroyTexture(targetTex);
	targetTex = nullptr;

	delete rect;
	rect = nullptr;
}


void Grid::update() {
	int tileSize =  rect->dest.w / gridSize;
	int margin = static_cast<int>(tileSize * 0.0625);

	int x = ((InputSystem::mouse[InputSystem::MOUSE::X] - rect->dest.x) / tileSize);
	int y = ((InputSystem::mouse[InputSystem::MOUSE::Y] - rect->dest.y) / tileSize);

	if (rect->CollidePoint(InputSystem::mouse[InputSystem::MOUSE::X], InputSystem::mouse[InputSystem::MOUSE::Y])) {
		if (grid[y][x] == 0) {
			if(InputSystem::mouse[InputSystem::MOUSE::LEFT]) {
				grid[y][x] = 2; // places wall
			}
		}

		if (grid[y][x] == 2) {
			if (InputSystem::mouse[InputSystem::MOUSE::RIGHT]) {
				grid[y][x] = 0; // erases wall
			}
		}
	}
}

// start / full path - red - #ff5258 - rgb(255, 82, 88)
// end - blue - #8d9cff - rgb(141, 156, 255)
// paths - yellow - #ffe946 - rgb(245, 255, 133)
// correct path - purple - #ff8fd0 - rgb(255, 143, 208)
// walls - gray - #9c9c9c - rgb(156, 156, 156)

void Grid::render() {
	int tileSize = rect->dest.w / gridSize;
	int margin = static_cast<int>(tileSize * 0.0625);


	SDL_Rect dest{ 0,0, tileSize - (2 * margin) , tileSize - (2 * margin) };
	for (unsigned int row = 0; row < grid.size(); row++) {
		for (unsigned int i = 0 ; i < grid[row].size(); i++) {

			dest.x = (i * tileSize) + margin + rect->dest.x;
			dest.y = (row * tileSize) + margin + rect->dest.y;

			switch (grid[row][i]) {
			case 0:
				continue;
			case 1: // uncalculated paths
				TM::renderDrawColor(245, 255, 133);
				break;
			case 2: // walls
				TM::renderDrawColor(156, 156, 156);
				break;
			case 3: // calculated path
				TM::renderDrawColor(255, 143, 208);
				break;
			case 4: // starting node / correct path
				TM::renderDrawColor(255, 82, 88);
				break;
			case 5: // ending node
				TM::renderDrawColor(141, 156, 255);
				break;
			}
			SDL_RenderFillRect(TM::renderer, &dest);
		}
	}
}

void Grid::renderGrid() {
	if (sizeChanged) {
		sizeChanged = false;
		SDL_DestroyTexture(targetTex);
		targetTex = SDL_CreateTexture(TM::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect->dest.w, rect->dest.w);
		SDL_SetRenderTarget(TM::renderer, targetTex);
		TM::SetAlphaBlending(targetTex);

		TM::renderDrawColor(gridColor);

		int tileSize = rect->dest.w / gridSize;
		for (int column = 1; column < gridSize; column++) {
			SDL_RenderDrawLine(TM::renderer,column * tileSize, 0, column * tileSize, rect->dest.w);
		}
		for (int row = 1; row < gridSize; row++) {
			SDL_RenderDrawLine(TM::renderer, 0, row * tileSize, rect->dest.w, row * tileSize);
		}
		SDL_SetRenderTarget(TM::renderer, NULL);
	}

	TM::DrawTexture(targetTex, rect->dest);
}

void Grid::sizeTo(int size) {
	gridSize = size;
	sizeChanged = true;

	grid.clear();
	for (int i = 0; i < gridSize; i++) {
		grid.push_back(std::vector<int>());
		for (int j = 0; j < gridSize; j++) {
			grid[i].push_back(0);
		}
	}
}

void Grid::color(int r, int g, int b) {
	gridColor.r = r;
	gridColor.g = g;
	gridColor.b = b;
}

void Grid::load() {
	if (GRID::RANDOM_WALLS) {
		for (unsigned int i = 0; i < grid.size(); i++) {
			for (unsigned int j = 0; j < grid[i].size(); j++) {
				if (rand() % 99 < GRID::RANDOM_WALLS_CHANCE) {
					grid[i][j] = 2;
				}
			}
		}
	}

	if (GRID::RANDOM_START) {
		int x = rand() % GRID::GRIDSIZE;
		int y = rand() % GRID::GRIDSIZE;

		grid[y][x] = 4;
	}
	else {
		grid[0][0] = 4;
	}

	if (GRID::RANDOM_END) {
		int x = rand() % GRID::GRIDSIZE;
		int y = rand() % GRID::GRIDSIZE;

		grid[y][x] = 5;
	}
	else {
		grid[GRID::GRIDSIZE - 1][GRID::GRIDSIZE - 1] = 5;
	}
}


