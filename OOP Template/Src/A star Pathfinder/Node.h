#pragma once
#include "../includes.h"


struct Node {
	Node() { };

	Node(int x_, int y_, int width) { // starting node
		x = x_;
		y = y_;
		g = 0;
		id = x + (y * width);
		parent = nullptr;
	}

	Node(Node& p, int x_, int y_, int width) {
		parent = new Node(p);
		x = x_;
		y = y_;
		id = x + (y * width);
	};

	void calculate(int gx, int gy) {
		g = parent->g + 1;
		h = abs(x - gx) + abs(y - gy);
		score = g + h;
	}

	void startCalculate(int gx, int gy) {
		g = 0;
		h = abs(x - gx) + abs(y - gy);
		score = g + h;
	}

	int x;
	int y;
	Node* parent = nullptr;
	int score = -1;
	int g = -1; // movement cost
	int h = -1; // heuristic
	Uint32 id; // how recent it is; bigger = younger
};

