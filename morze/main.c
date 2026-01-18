#if _MSC_VER
#pragma execution_character_set("utf-8")
#endif

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
	
	int window_width = 800;
	int window_height = 600;

	SDL_Window* window = SDL_CreateWindow(
		"Тренажёр Морзе",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		window_width, window_height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	SDL_SetWindowMinimumSize(window, 800, 600);


	SDL_Renderer* renderer = SDL_CreateRenderer(
		window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	// Шрифт

	int font_size = 24;
	int line_spacing = 5;

	TTF_Font* font = TTF_OpenFont("fonts/RenaultLife.ttf", font_size);
	if (!font) {
		printf("Выполнение программы невозможно: Ошибка загрузки шрифта");
		return 1;
	}

	// Инициализация иных переменных

	char* scene = "Начальный экран";
	
	int scroll_offset = 0;
	int max_scroll_offset = 0;

	// Основной цикл
	
	int running = 1;
	SDL_Event event;

	while(running){

		// Обработка событий

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}

			if (event.type == SDL_MOUSEWHEEL) {
				if (event.wheel.y > 0) {
					scroll_offset -= 25;
					if (scroll_offset < 0) scroll_offset = 0;
				}
				else if (event.wheel.y < 0) {
					scroll_offset += 25;
					if (scroll_offset > max_scroll_offset) scroll_offset = max_scroll_offset;
				}
			}

			if (event.type == SDL_KEYDOWN) {
				
				// Глобальные функции нажатия клавиш
				
				if (event.key.keysym.sym == SDLK_RETURN) {
					if (scene == "Начальный экран") scene = "Выбор режима";
				}

				// Локальные функции нажатия клавиш

				if (scene == "Выбор режима") {
					if ((event.key.keysym.sym == SDLK_1) || (event.key.keysym.sym == SDLK_KP_1)) {
						scene = "Азбука Морзе";
						scroll_offset = 0;
						max_scroll_offset = 400;
					}
				}
				if ((scene == "Азбука Морзе") && (event.key.keysym.sym == SDLK_ESCAPE)) {
					scene = "Выбор режима";
					scroll_offset = 0;
					max_scroll_offset = 0;
				}
			}
		}

		// Очистка экрана

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		// Обновление размеров экрана

		SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

		// Графика

		if (scene == "Начальный экран") { // Начальный экран
			draw_text_line(
				renderer,
				font,
				"Тренажёр Морзе",
				window_width / 2, window_height / 2 - font_size / 2 - line_spacing / 2,
				255, 255, 255,
				1, 1
			);
			draw_text_line(
				renderer,
				font,
				"Нажмите Enter чтобы продолжить",
				window_width / 2, window_height / 2 + font_size / 2 + line_spacing / 2,
				100, 100, 100,
				1, 1
			);
		}
		else if (scene == "Выбор режима") { // Выбор режима
			draw_text_line(
				renderer,
				font,
				"1 - Азбука Морзе",
				window_width / 2, window_height / 2 - font_size * 3 / 2 - line_spacing / 2,
				255, 255, 255,
				1, 1
			);
			draw_text_line(
				renderer,
				font,
				"2 - Изучение букв",
				window_width / 2, window_height / 2 - font_size / 2 - line_spacing / 2,
				255, 255, 255,
				1, 1
			);
			draw_text_line(
				renderer,
				font,
				"3 - Повторение букв",
				window_width / 2, window_height / 2 + font_size / 2 + line_spacing / 2,
				255, 255, 255,
				1, 1
			);
			draw_text_line(
				renderer,
				font,
				"Нажмите цифру, соответствующую номеру режима",
				line_spacing, window_height - line_spacing,
				100, 100, 100,
				0, 2
			);
		}

		else if (scene == "Азбука Морзе") {
			draw_text_line(
				renderer,
				font,
				"Азбука Морзе",
				window_width / 2, line_spacing - scroll_offset,
				255, 255, 255,
				1, 0
			);

			// RU_primer

			int draw_y_pos = line_spacing * 3 + font_size;
			int draw_x_pos = line_spacing * 3;

			for (int i = 0; i < RU_primer_lenght; i++) {
				draw_text_line(
					renderer,
					font,
					RU_primer[i].letter,
					draw_x_pos, draw_y_pos - scroll_offset,
					255, 255, 255,
					0, 0
				);

				draw_text_line(
					renderer,
					font,
					RU_primer[i].code,
					draw_x_pos + 50, draw_y_pos - scroll_offset,
					255, 255, 255,
					0, 0
				);

				draw_y_pos += line_spacing + font_size;
			}

			// EN_primer

			draw_y_pos = line_spacing * 3 + font_size;
			draw_x_pos = window_width / 2 - 25;

			for (int i = 0; i < EN_primer_lenght; i++) {
				draw_text_line(
					renderer,
					font,
					EN_primer[i].letter,
					draw_x_pos, draw_y_pos - scroll_offset,
					255, 255, 255,
					0, 0
				);

				draw_text_line(
					renderer,
					font,
					EN_primer[i].code,
					draw_x_pos + 50, draw_y_pos - scroll_offset,
					255, 255, 255,
					0, 0
				);

				draw_y_pos += line_spacing + font_size;
			}

			// DIGIT_primer

			draw_y_pos = line_spacing * 3 + font_size;
			draw_x_pos = window_width - line_spacing * 3 - 2 * font_size - 50;

			for (int i = 0; i < DIGIT_primer_lenght; i++) {
				draw_text_line(
					renderer,
					font,
					DIGIT_primer[i].letter,
					draw_x_pos, draw_y_pos - scroll_offset,
					255, 255, 255,
					0, 0
				);

				draw_text_line(
					renderer,
					font,
					DIGIT_primer[i].code,
					draw_x_pos + 50, draw_y_pos - scroll_offset,
					255, 255, 255,
					0, 0
				);

				draw_y_pos += line_spacing + font_size;
			}

			// PUNCTUATION_primer

			draw_y_pos += 50;

			for (int i = 0; i < PUNCTUATION_primer_lenght; i++) {
				draw_text_line(
					renderer,
					font,
					PUNCTUATION_primer[i].letter,
					draw_x_pos, draw_y_pos - scroll_offset,
					255, 255, 255,
					3, 0
				);

				draw_text_line(
					renderer,
					font,
					PUNCTUATION_primer[i].code,
					draw_x_pos + 50, draw_y_pos - scroll_offset,
					255, 255, 255,
					3, 0
				);

				draw_y_pos += line_spacing + font_size;
			}
		}

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