#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
 
#include <SDL.h>
#include <SDL_ttf.h>

#include "GUI.h"
#include "morse_alphabet.h"

int main(void) {
	char* locale = setlocale(LC_ALL, "");

	// Инициализация SDL2, SDL_ttf

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Выполнение программы невозможно: Библиотека SDL 2 не инициализирована");
		return 1;
	}
    TTF_Init();
	
	// Создание окна и рендера

	SDL_Window* window = SDL_CreateWindow(
		"the Morse simulator",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, 
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(
		window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

    // Шрифт

    TTF_Font* font = TTF_OpenFont("fonts/RenaultLife.ttf", 24);
    if (!font) {
        printf("Выполнение программы невозможно: Ошибка загрузки шрифта");
        return 1;
    }
	
	// Основной цикл

	int running = 1;
	SDL_Event event;

    while(running){

        // Обработка событий

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
            }
        }

        // Очистка экрана

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Графика

        const char* texxt = "Hello, world!?";
        draw_text(renderer, font, texxt, 10, 10, 255, 255, 255);

        // Показать кадр

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Освобождение ресурсов

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    TTF_CloseFont(font);
    TTF_Quit();

    return 0;
}