#include "Setup.h"

float NODE::G = 0.8f;

bool GRID::GRIDSIZE_CHANGED = false;
unsigned int GRID::GRIDSIZE = 150;

bool GRID::RANDOM_WALLS = true;
bool GRID::RANDOM_START = true;
bool GRID::RANDOM_END = true;
unsigned int GRID::RANDOM_WALLS_CHANCE = 30;

unsigned int GRID::WIDTH = 900;
unsigned int GRID::HEIGHT = 900;

bool GRID::AUTORESET = false;
bool GRID::RESET = false;

int GRID::X = 100;
int GRID::Y = 0;