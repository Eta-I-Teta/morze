#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

void draw_text(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    int x, int y,
    Uint8 r, Uint8 g, Uint8 b
);