#include "FRect.h"
#include "Rect.h"

FRect::FRect() {
	left = right = top = bottom = 0.0f;
	dest.x = dest.w = dest.y = dest.h = 0;
	center[0] = 0.0f;
	center[1] = 0.0f;
}

FRect::FRect(const float x, const float y, const float w, const float h) {
	setup(x, y, w, h);
}


bool FRect::CollideRect(const FRect& target) const {
	return (left < target.right &&
			right > target.left &&
			bottom > target.top &&
			top < target.bottom);
}

bool FRect::CollideRect(const Rect& target) const {
	return ((int)left < target.right &&
			(int)right > target.left &&
			(int)bottom > target.top &&
			(int)top < target.bottom);
}


void FRect::renderOutline(int R = 255, int G = 0, int B = 0) const {
	SDL_SetRenderDrawColor(TM::renderer, (Uint8)R, (Uint8)G, (Uint8)B, 255);
	SDL_RenderDrawRect(TM::renderer, &dest);
}

void FRect::renderOutline(const Uint8 R = 255, const Uint8 G = 0, const Uint8 B = 0) const {
	SDL_SetRenderDrawColor(TM::renderer, R, G, B, 255);
	SDL_RenderDrawRect(TM::renderer, &dest);
}

void FRect::renderOutline(const SDL_Color& color) const {
	SDL_SetRenderDrawColor(TM::renderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawRect(TM::renderer, &dest);
}

void FRect::renderFill(int R = 255, int G = 0, int B = 0, int A = 255)  const {
	SDL_SetRenderDrawColor(TM::renderer, R, G, B, A);
	SDL_RenderFillRect(TM::renderer, &dest);
}

void FRect::renderFill(const Uint8 R = 255, const Uint8 G = 0, const Uint8 B = 0, const Uint8 A = 255) const {
	SDL_SetRenderDrawColor(TM::renderer, R, G, B, A);
	SDL_RenderFillRect(TM::renderer, &dest);
}

void FRect::renderFill(const SDL_Color& color) const {
	SDL_SetRenderDrawColor(TM::renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(TM::renderer, &dest);
}

void FRect::setup(const float x, const float y, const float w, const float h) {
	dest.x = (int)x;
	dest.y = (int)y;
	dest.w = (int)w;
	dest.h = (int)h;

	left = x;
	right = x + w;
	top = y;
	bottom = y + h;

	center[0] = x + (w / 2.0f);
	center[1] = y + (h / 2.0f);
}

void FRect::update() {
	left = (float)dest.x;
	top = (float)dest.y;
	right = (float)dest.x + (float)dest.w;
	bottom = (float)dest.y + (float)dest.h;

	center[0] = left + (dest.w / 2.0f);
	center[1] = top + (dest.h / 2.0f);
}