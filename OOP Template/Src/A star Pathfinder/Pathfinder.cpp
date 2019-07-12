#include "Pathfinder.h"

Pathfinder::Pathfinder(std::vector<std::vector<int>>& grid) {
	
	// put start block into closed list
	// find end block
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == 4) {
				Node tmp(j, i, grid[0].size());
				closedList[tmp.id] = tmp;
				startX = j;
				startY = i;
			}
			if (grid[i][j] == 5) {
				goalX = j;
				goalY = i;
			}
		}
	}
	closedList[startX + (startY * grid[0].size())].startCalculate(goalX, goalY);

	// calculate start's adjacent
	calcAdjacent(startX, startY, grid);
}

void Pathfinder::update(std::vector<std::vector<int>>& grid) {
	if (!finished) {
		// get lowest score on the open list and move it to the closed list
		unsigned int lowestScore = -1;
		Uint32 id = -1;
		for (auto it = openList.begin(); it != openList.end(); it++) {
			if (it.value().score < lowestScore) {
				lowestScore = it.value().score;
				id = it.value().id;
			}
		}
		closedList[id] = openList[id];
		openList.erase(id);

		
		if (closedList[id].x == goalX && closedList[id].y == goalY) { //only color if it doesn't cover the goal
			finished = true;
		}
		else {
			grid[closedList[id].y][closedList[id].x] = 3;
			calcAdjacent(closedList[id].x, closedList[id].y, grid);
		}
	}

	if (finished && !drawnPath) {
		for (auto it = closedList.begin(); it != closedList.end(); it++) {
			if (it.value().x == goalX && it.value().y == goalY) {
				recursePath(it.value(), grid);
				break;
			}
		}
	}
}

bool Pathfinder::available(int x, int y, std::vector<std::vector<int>>& grid) {
	//std::cout << "ID #" << x + (y * grid[0].size()) << " (" << x << ", "<<y<<") : ";

	if (x < 0 || x >= (int)grid[0].size() || y < 0 || y >= (int)grid.size()) { // boundaries
		//std::cout << "Out of bounds\n" << std::endl;
		return false;
	}

	if (grid[y][x] == 2) { // wall
		//std::cout << "Wall" << std::endl;
		return false; 
	}

	if (closedList.find(x + (y * grid[0].size())) != closedList.end()) { // is it in the closedList?
		//std::cout << "In closed list" << std::endl;
		return false; 
	}

	//std::cout << "Available" << std::endl;
	return true;
}

void Pathfinder::calcAdjacent(int x, int y, std::vector<std::vector<int>>& grid) {
	// 4 way movement
	// for each square T in S' adjacent tiles
		// if T is in the closed list, ignore it

		// if T is not in the open list, add it and compute its score

		// if T is already in the open list, check if the score is lower when we use
		// the generated path to get there. If it is, update its score and its parent

	if (available(x - 1, y, grid)) {
		calculate(x, y, -1, 0, grid);
	}
	if (available(x + 1, y, grid)) {
		calculate(x, y, 1, 0, grid);
	}
	if (available(x, y - 1, grid)) {
		calculate(x, y, 0, -1, grid);
	}
	if (available(x, y + 1, grid)) {
		calculate(x, y, 0, 1, grid);
	}
}

void Pathfinder::calculate(int x, int y, int xoffset, int yoffset, std::vector<std::vector<int>>& grid) {
	Node tmp(closedList[x + (y * grid[0].size())], x + xoffset, y + yoffset, grid[0].size());
	//pass in parent node and init

	tmp.calculate(goalX, goalY);
	//calculate h and f

	if (openList.find(x + (y * grid[0].size())) != openList.end()) {
		if (openList[x + (y * grid[0].size())].score < tmp.score) {
			calcAdjacent(x + xoffset, y + yoffset, grid);
			return;
		}
	}


	openList[tmp.id] = tmp;
	//move it into openList

	if (y + yoffset != goalY || x + xoffset != goalX) {
		grid[y + yoffset][x + xoffset] = 1;
	}
	//set the node spot to yellow IF it doesn't cover the goal
}

void Pathfinder::recursePath(Node& node, std::vector<std::vector<int>>& grid) {
	if (node.parent != nullptr && !drawnPath) {
		//std::cout << node.x << " " << node.y << " " << node.id << std::endl;
		grid[node.y][node.x] = 4;
		recursePath(*node.parent, grid);
	}
	drawnPath = true;
}