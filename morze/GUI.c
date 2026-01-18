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