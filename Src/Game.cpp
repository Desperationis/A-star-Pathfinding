#include "Game.h"
#include "Tools/Font.h"
#include "Tools/Timer.h"
#include "Tools/InputSystem.h"
#include "Tools/TM.h"
#include "Grid/Grid.h"
#include "Knobs/Button.h"
#include "Setup.h"

#include "Pathfinder/Pathfinder.h"

Grid* grid = nullptr;
Pathfinder* pathfinder;

enum BUTTONS { AUTORESET, RESET };
std::vector<Button*> buttons;

Game::Game(const char* name, int xpos, int ypos, int width, int height, Uint32 flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL failed to Initalize");
		system("pause");
	}

	if(TTF_Init() != 0) {
		printf("SDL_TTF failed to Initalize");
		system("pause");
	}

	window = SDL_CreateWindow(name, xpos, ypos, width, height, flags);
	TM::rendererInit(window);
	TM::renderDrawColor(255,255,255);
	running = true;
	fpsTimer = new Timer();
	fpsTimer->start();
	SDL_PollEvent(&event);

	grid = new Grid(GRID::GRIDSIZE);
	grid->load();


	pathfinder = new Pathfinder(grid->grid);


	// It is important they are aligned with their enumerations
	int x = GRID::X + GRID::WIDTH + 20;

	buttons.push_back(new Button(GRID::AUTORESET, " AUTORESET ", x, 100));
	buttons.push_back(new Button(GRID::RESET, " RESET ", x, 150));

	buttons.push_back(new Button(GRID::RANDOM_WALLS, " RANDOM WALLS ", x, 250));
	buttons.push_back(new Button(GRID::RANDOM_START, " RANDOM START ", x, 300));
	buttons.push_back(new Button(GRID::RANDOM_END, " RANDOM END ", x, 350));

	buttons[RESET]->oneClick = false;
}


void Game::update() {
	//updates grid
	grid->update();

	// refreshes frame rate counter
	if (counter) {
		if (fpsTimer->getTicks() > 10000) {
			fpsTimer->stop();
			fpsTimer->start();
			countedFrames = 0;
		}
		float avgFPS = countedFrames / (fpsTimer->getTicks() / 1000.0f);
		if (avgFPS > 2000000) {
			avgFPS = 0;
		}
		std::cout << avgFPS << std::endl;
	}

	if (countedFrames % 1 == 0) {
		pathfinder->update(grid->grid);
	}

	if ((pathfinder->isFinished() && GRID::AUTORESET) || GRID::GRIDSIZE_CHANGED || GRID::RESET) {
		GRID::GRIDSIZE_CHANGED = false;
		delete grid;
		delete pathfinder;

		grid = new Grid(GRID::GRIDSIZE);
		grid->load();

		pathfinder = new Pathfinder(grid->grid);
		GRID::RESET = false;
	}
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->update();
	}

}

void Game::render() {
	TM::renderClear();

	grid->render();
	grid->renderGrid();

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->render();
	}

	TM::renderDrawColor(255, 255, 255);
	TM::renderPresent();
	countedFrames++;
}

bool TAB_PRESSED = false;
void Game::events() {
	InputSystem::PumpEvents();
	
	while(SDL_PollEvent(&event)) {
		switch (event.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			running = false;
		}

		if (InputSystem::keys[SDL_SCANCODE_ESCAPE]) {
			running = false;
		}

		if (InputSystem::keys[SDL_SCANCODE_TAB] && !TAB_PRESSED) {
			counter = !counter;
		}
		TAB_PRESSED = InputSystem::keys[SDL_SCANCODE_TAB];
	}
}

bool Game::isRunning() const {
	return running;
}
