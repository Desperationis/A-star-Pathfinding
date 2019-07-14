#include "Button.h"
#include "../Tools/TM.h"
#include "../Tools/Rect.h"
#include "../Tools/Font.h"
#include "../Tools/InputSystem.h"

Button::Button(bool& boo, const char* text, int x, int y) {
	toggle = &boo;

	//init font

	font = new Font("Fonts//8bitoperator_jve.ttf", 40);
	font->loadRenderType(Font::SHADED);
	font->loadColor(255, 255, 255, 255);
	font->loadShadeColor(50, 50, 50, 255);

	//init texture

	texture = font->toText(text);
	TM::SetAlphaBlending(texture);

	//init rect
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	rect = new Rect(x,y,w,h);
}

Button::~Button() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Button::render() {
	if (*toggle) {
		TM::SetAlpha(texture, 100);
	}
	else {
		TM::SetAlpha(texture,255);
	}
	TM::DrawTexture(texture, rect->dest);
}

void Button::update() {
	bool clicked = InputSystem::mouse[InputSystem::MOUSE::LEFT];

	if (clicked && (!pressed || !oneClick)) {
		bool hit = rect->CollidePoint(InputSystem::mouse[InputSystem::MOUSE::X], InputSystem::mouse[InputSystem::MOUSE::Y]);
		if (hit) {
			*toggle = !(*toggle);
		}
	}
	pressed = clicked;
}