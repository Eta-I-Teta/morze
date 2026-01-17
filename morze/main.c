#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
 
#include <SDL.h>

#include "morse_alphabet.h"

int main(void) {
	char* locale = setlocale(LC_ALL, "");

	// Обработка ошибки инициализации SDL

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Выполнение программы невозможно: Библиотека SDL не инициализирована");
		return 1;
	}
	
	// Создание окна и рендера

	SDL_Window* window = SDL_CreateWindow(
		"Учебник Морзе",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, 
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(
		window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	
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

        // Очистка экрана (фон)
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // тёмно-серый
        SDL_RenderClear(renderer);

        // === СЮДА БУДЕТ ТВОЯ ГРАФИКА ===

        // Пример: красный прямоугольник
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect = { 100, 100, 200, 100 };
        SDL_RenderFillRect(renderer, &rect);

        // Показать кадр
        SDL_RenderPresent(renderer);
    }

    // Освобождение ресурсов

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}