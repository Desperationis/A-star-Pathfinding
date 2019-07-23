#pragma once
#include "SDl.h"


struct Rect;
class Font;
class Button {
public:
	Button(bool& boo, const char* text, int x, int y);
	~Button();

	void update();
	void render();

	bool oneClick = true;
private:
	Rect* rect;
	SDL_Texture* texture;
	Font* font;

	bool pressed = false; //to avoid toggling the button every frame
	bool* toggle = nullptr;
};

