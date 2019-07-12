#pragma once
#include "hopscotch_map.h"

#include "Node.h"
// not good practice at all....

struct Node;
class Pathfinder {
public:
	Pathfinder(std::vector<std::vector<int>>& grid);

	void update(std::vector<std::vector<int>>& grid);
	bool available(int x, int y, std::vector<std::vector<int>>& grid); // checks to see if a tile is available
	void calculate(int x, int y, int xoffset, int yoffset, std::vector<std::vector<int>>& grid);
private:
	void calcAdjacent(int x, int y, std::vector<std::vector<int>>& grid); // calculates adjacent tiles and adds them to open list

	tsl::hopscotch_map<Uint32, Node> closedList; // id's that aren't being considered to find the shortest path (i.e. the possible path)
	tsl::hopscotch_map<Uint32, Node> openList; // tiles that are being considered to find the shortest path
	bool finished = false;

	int goalX = -1;
	int goalY = -1;

	int startX = -1;
	int startY = -1;
};