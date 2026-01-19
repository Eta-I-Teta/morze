#include "GUI.h"

void draw_text_line(
	SDL_Renderer* renderer,
	TTF_Font* font,
	const char* text,
	int x, int y,
	Uint8 r, Uint8 g, Uint8 b,
	int horizontal_align,
	int vertical_align
) {

	SDL_Color color = { r, g, b, 255 };
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
	if (!surface) return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture) {

		if (horizontal_align == 2) x -= surface->w;
		else if (horizontal_align == 1) x -= (surface->w) / 2;
		else x = x;

		if (vertical_align == 2) y -= surface->h;
		else if (vertical_align == 1) y -= (surface->h) / 2;
		else y = y;

		SDL_Rect rect = {
			x, y,
			surface->w, surface->h
		};

		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_DestroyTexture(texture);

	}

	SDL_FreeSurface(surface);

};

void draw_cross(
	SDL_Renderer* renderer,
	int x, int y,
	int size,
	int thickness,
	Uint8 r, Uint8 g, Uint8 b,
	int horizontal_align,
	int vertical_align
) {
	
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);

	int horizontal_align_offset;
	int vertical_align_offset;

	if (horizontal_align == 0) horizontal_align_offset = 0;
	else if (horizontal_align == 1) horizontal_align_offset = size / 2;
	else horizontal_align_offset = size;

	if (vertical_align == 0) vertical_align_offset = 0;
	else if (vertical_align == 1) vertical_align_offset = size / 2;
	else vertical_align_offset = size;

	for (int pixel = 0; pixel <= thickness; pixel++) {
		SDL_RenderDrawLine(
			renderer,
			x - horizontal_align_offset + pixel, y - vertical_align_offset,
			x + size - thickness - horizontal_align_offset + pixel, y + size - vertical_align_offset
		);
		SDL_RenderDrawLine(
			renderer,
			x + size - thickness - horizontal_align_offset + pixel, y - vertical_align_offset,
			x - horizontal_align_offset + pixel, y + size - vertical_align_offset
		);
	};

}

void draw_checkmark(
	SDL_Renderer* renderer,
	int x, int y,
	int size,
	int thickness,
	Uint8 r, Uint8 g, Uint8 b,
	int horizontal_align,
	int vertical_align
) {

	SDL_SetRenderDrawColor(renderer, r, g, b, 255);

	int horizontal_align_offset;
	int vertical_align_offset;

	if (horizontal_align == 0) horizontal_align_offset = 0;
	else if (horizontal_align == 1) horizontal_align_offset = size / 2;
	else horizontal_align_offset = size;

	if (vertical_align == 0) vertical_align_offset = 0;
	else if (vertical_align == 1) vertical_align_offset = size / 2;
	else vertical_align_offset = size;

	for (int pixel = 0; pixel <= thickness; pixel++) {
		SDL_RenderDrawLine(
			renderer,
			x - horizontal_align_offset + pixel, y + size / 2 - vertical_align_offset,
			x + size / 3 - thickness / 2 - horizontal_align_offset + pixel, y + size - vertical_align_offset
		);
		SDL_RenderDrawLine(
			renderer,
			x + size / 3 - thickness / 2 - horizontal_align_offset + pixel, y + size - vertical_align_offset,
			x + size - thickness - horizontal_align_offset + pixel, y - vertical_align_offset
		);
	};

}