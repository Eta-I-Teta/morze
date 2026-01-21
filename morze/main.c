#if _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <time.h>
 
#include <SDL.h>
#include <SDL_ttf.h>

#include "GUI.h"
#include "morse_alphabet.h"
#include "audio.h"
#include "scenes.h"
#include "training.h"
#include "other_settings.h"

int main(void) {
	char* locale = setlocale(LC_ALL, "");

	// Инициализация SDL2, SDL_ttf, time

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Выполнение программы невозможно: Библиотека SDL 2 (SDL_INIT_VIDEO) не инициализирована");
		return 1;
	}
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		printf("Выполнение программы невозможно: Библиотека SDL 2 (SDL_INIT_AUDIO) не инициализирована");
		return 1;
	}
	if (TTF_Init() != 0) {
		printf("Выполнение программы невозможно: Библиотека SDL_ttf не инициализирована");
		return 1;
	}

	srand((unsigned int)time(NULL));
	
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

	const int line_spacing = 5;

	const int font_size = 24;
	TTF_Font* font = TTF_OpenFont("fonts/0_MilligramVariable-Roman.ttf", font_size);
	if (!font) {
		printf("Выполнение программы невозможно: Ошибка загрузки шрифта (font)");
		return 1;
	}

	const int giant_font_size = 120;
	TTF_Font* giant_font = TTF_OpenFont("fonts/0_MilligramVariable-Roman.ttf", giant_font_size);
	if (!font) {
		printf("Выполнение программы невозможно: Ошибка загрузки шрифта (giant_font)");
		return 1;
	}

	// Инициализация иных переменных

	char* scene = "Начальный экран";
	
	int scroll_offset = 0;
	int max_scroll_offset = 0;

	TrainingState* training_state = malloc(sizeof(TrainingState));
	if (training_state != NULL)init_training_state(training_state);
	else {
		printf("Выполнение программы невозможно: Ошибка выделения памяти (training_state)");
		return 1;
	}

	OtherSettings* other_settings = create_other_settings();

	int is_space_held = 0;
	int held_start;
	int held;

	// Основной цикл
	
	int running = 1;
	SDL_Event event;

	while(running){

		// Обработка событий

		while (SDL_PollEvent(&event)) {
			
			// Событие закрытия

			if (event.type == SDL_QUIT) {
				running = 0;
			}

			// Событие прокрутки

			if (event.type == SDL_MOUSEWHEEL) {
				if (event.wheel.y > 0) {
					scroll_offset -= 35;
					if (scroll_offset < 0) scroll_offset = 0;
				}
				else if (event.wheel.y < 0) {
					scroll_offset += 35;
					if (scroll_offset > max_scroll_offset) scroll_offset = max_scroll_offset;
				}
			}

			// События нажатия

			if (event.type == SDL_KEYDOWN) {
				
				// Глобальные функции нажатия клавиш

				if (event.key.keysym.sym == SDLK_SPACE) {
					if (!is_space_held) {
						held_start = SDL_GetTicks();
						is_space_held = 1;
					}
					//play_beep(100, 800);
				}

				// Локальные функции нажатия клавиш

				if ((scene == "Начальный экран") &&
					((event.key.keysym.sym == SDLK_RETURN) || (event.key.keysym.sym == SDLK_KP_ENTER))) scene = "Выбор режима";

				else if (scene == "Выбор режима") {
					if (event.key.keysym.sym == SDLK_ESCAPE) running = 0;

					if ((event.key.keysym.sym == SDLK_1) || (event.key.keysym.sym == SDLK_KP_1)) {
						scene = "Азбука Морзе";

						scroll_offset = 0;
						max_scroll_offset = 400;
					}
					if ((event.key.keysym.sym == SDLK_2) || (event.key.keysym.sym == SDLK_KP_2)) {
						scene = "Изучение";

						training_state->stage = 0;
						training_state->mistakes = 0;

						clear_input(training_state);
						update_pair_to_learn(training_state);
					}
					if ((event.key.keysym.sym == SDLK_3) || (event.key.keysym.sym == SDLK_KP_3)) {
						scene = "Тренировка";

						training_state->stage = 0;
						training_state->mistakes = 0;

						clear_input(training_state);
						update_pair_to_learn(training_state);
					}

					if ((event.key.keysym.sym == SDLK_9) || (event.key.keysym.sym == SDLK_KP_9)) scene = "Выбор букварей";
					if ((event.key.keysym.sym == SDLK_0) || (event.key.keysym.sym == SDLK_KP_0)) scene = "Прочие настройки";
				}

				else if ((scene == "Азбука Морзе") && (event.key.keysym.sym == SDLK_ESCAPE)) {
					scene = "Выбор режима";
					scroll_offset = 0;
					max_scroll_offset = 0;
				}
				else if ((scene == "Изучение") && (event.key.keysym.sym == SDLK_ESCAPE)) scene = "Результат тренировки";
				else if ((scene == "Тренировка") && (event.key.keysym.sym == SDLK_ESCAPE)) scene = "Результат тренировки";

				else if ((scene == "Результат тренировки") &&
					     ((event.key.keysym.sym == SDLK_ESCAPE) || (event.key.keysym.sym == SDLK_RETURN) || 
						 (event.key.keysym.sym == SDLK_KP_ENTER))) scene = "Выбор режима";

				else if (scene == "Выбор букварей") {
					if (event.key.keysym.sym == SDLK_ESCAPE) scene = "Выбор режима";

					if (
						(event.key.keysym.sym == SDLK_e) && 
						(!primer_status.EN || primer_status.RU || primer_status.DIGIT || primer_status.PUNCTUATION)
					) primer_status.EN = !primer_status.EN;
					if (
						(event.key.keysym.sym == SDLK_r) &&
						(primer_status.EN || !primer_status.RU || primer_status.DIGIT || primer_status.PUNCTUATION)
						) primer_status.RU = !primer_status.RU;
					if (
						(event.key.keysym.sym == SDLK_d) &&
						(primer_status.EN || primer_status.RU || !primer_status.DIGIT || primer_status.PUNCTUATION)
						) primer_status.DIGIT = !primer_status.DIGIT;
					if (
						(event.key.keysym.sym == SDLK_p) &&
						(primer_status.EN || primer_status.RU || primer_status.DIGIT || !primer_status.PUNCTUATION)
						) primer_status.PUNCTUATION = !primer_status.PUNCTUATION;
				}
				else if (scene == "Прочие настройки") {
					if (event.key.keysym.sym == SDLK_ESCAPE) scene = "Выбор режима";

					
				}

			}

			// События отжатия

			if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_SPACE)) {
				is_space_held = 0;
				held = SDL_GetTicks() - held_start;

				if (training_state->input_index >= training_state->input_code_lenght) clear_input(training_state);

				if (held < other_settings->DOT_THRESHOLD) {
					training_state->input_code[training_state->input_index] = '.';
					training_state->input_index++;
				}
				else {
					training_state->input_code[training_state->input_index] = '-';
					training_state->input_index++;
				}
			}

		}

		// Очистка экрана

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		// Обновление размеров экрана

		SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

		// Графика

		scene = draw_scene(

			renderer,
			scene,

			font, font_size,
			giant_font, giant_font_size,
			line_spacing,

			window_width, window_height,
			scroll_offset,

			training_state,

			other_settings

		);

		// Показать кадр

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	// Освобождение ресурсов

	free(training_state);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	TTF_CloseFont(font);
	TTF_CloseFont(giant_font);
	TTF_Quit();

	return 0;
}