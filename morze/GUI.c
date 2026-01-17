#include "GUI.h"

void draw_text(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    int x, int y,
    Uint8 r, Uint8 g, Uint8 b
)
{
    SDL_Color color = { r, g, b, 255 };
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture) {
        SDL_Rect rect = {
            x, y,
            surface->w, surface->h
        };
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_DestroyTexture(texture);
    }
    SDL_FreeSurface(surface);
};