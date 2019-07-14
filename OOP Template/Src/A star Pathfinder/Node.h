#pragma once
#include "../includes.h"


struct Node {
	Node() { };

	Node(int x_, int y_, int width) { // starting node
		x = x_;
		y = y_;
		g = 0.0f;
		id = x + (y * width);
	}

	Node(Node& p, int x_, int y_, int width) {
		parent = new Node(p);
		x = x_;
		y = y_;
		id = x + (y * width);
	};

	~Node() {
		parent = nullptr;
	}


	void calculate(int gx, int gy) {
		g = parent->g + 0.7f;
		h = static_cast<float>(abs(x - gx) + abs(y - gy));
		score = g + h;
	}

	void startCalculate(int gx, int gy) {
		g = 0.0f;
		h = static_cast<float>(abs(x - gx) + abs(y - gy));
		score = g + h;
	}

	int x;
	int y;
	Node* parent = nullptr;
	float score = -1.0f;
	float g = -1.0f; // movement cost
	float h = -1.0f; // heuristic
	Uint32 id; // how recent it is; bigger = younger
};

