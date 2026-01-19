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

int main(void) {
	char* locale = setlocale(LC_ALL, "");

	// Инициализация SDL2, SDL_ttf, time

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Выполнение программы невозможно: Библиотека SDL 2 не инициализирована");
		return 1;
	}
	TTF_Init();

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
	TTF_Font* font = TTF_OpenFont("fonts/RenaultLife.ttf", font_size);
	if (!font) {
		printf("Выполнение программы невозможно: Ошибка загрузки шрифта (font)");
		return 1;
	}

	const int giant_font_size = 120;
	TTF_Font* giant_font = TTF_OpenFont("fonts/RenaultLife.ttf", giant_font_size);
	if (!font) {
		printf("Выполнение программы невозможно: Ошибка загрузки шрифта (giant_font)");
		return 1;
	}

	// Инициализация иных переменных

	char* scene = "Начальный экран";
	
	int scroll_offset = 0;
	int max_scroll_offset = 0;

	int training_stage = 0;

	int pair_to_learn_count = 3;
	LettersPair pair_to_learn[3];

	int mistakes_counter = 0;

	char buffer_for_int_as_string[32 + 16];

	int DOT_THRESHOLD = 250;

	char input_code[17];
	input_code[16] = '\0';
	int input_index = 0;
	const int input_code_lenght = 16;

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
				
				if ((event.key.keysym.sym == SDLK_SPACE) && (!is_space_held)) {
					held_start = SDL_GetTicks();
					is_space_held = 1;
				}

				// Локальные функции нажатия клавиш

				if ((scene == "Начальный экран") && 
					((event.key.keysym.sym == SDLK_RETURN) || (event.key.keysym.sym == SDLK_KP_ENTER))) scene = "Выбор режима";

				if (scene == "Выбор режима") {
					if (event.key.keysym.sym == SDLK_ESCAPE) running = 0;

					if ((event.key.keysym.sym == SDLK_1) || (event.key.keysym.sym == SDLK_KP_1)) {
						scene = "Азбука Морзе";

						scroll_offset = 0;
						max_scroll_offset = 400;
					}
					if ((event.key.keysym.sym == SDLK_2) || (event.key.keysym.sym == SDLK_KP_2)) {
						scene = "Изучение";

						training_stage = 0;
						for (int i = 0; i < pair_to_learn_count; i++) pair_to_learn[i] = get_random_pair();

						mistakes_counter = 0;
						input_index = 0;
						for (int i = 0; i < input_code_lenght; i++) input_code[i] = '\0';
					}

					if ((event.key.keysym.sym == SDLK_0) || (event.key.keysym.sym == SDLK_KP_0)) scene = "Выбор букварей";
				}

				if ((scene == "Азбука Морзе") && (event.key.keysym.sym == SDLK_ESCAPE)) {
					scene = "Выбор режима";
					scroll_offset = 0;
					max_scroll_offset = 0;
				}
				if ((scene == "Изучение") && (event.key.keysym.sym == SDLK_ESCAPE)) scene = "Результат тренировки";

				if ((scene == "Результат тренировки") && (event.key.keysym.sym == SDLK_ESCAPE)) scene = "Выбор режима";

				if (scene == "Выбор букварей") {
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

			}

			// События отжатия

			if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_SPACE)) {
				is_space_held = 0;
				held = SDL_GetTicks() - held_start;

				if (input_index >= input_code_lenght) {
					input_index = 0;
					for (int i = 0; i < input_code_lenght; i++) input_code[i] = '\0';
				}

				if (held < DOT_THRESHOLD) {
					input_code[input_index] = '.';
					input_index++;
				}
				else {
					input_code[input_index] = '-';
					input_index++;
				}
			}

		}

		// Очистка экрана

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		// Обновление размеров экрана

		SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

		// Графика

		int draw_y_pos = 0;
		int draw_x_pos = 0;

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
				"2 - Изучение",
				window_width / 2, window_height / 2 - font_size / 2 - line_spacing / 2,
				255, 255, 255,
				1, 1
			);
			draw_text_line(
				renderer,
				font,
				"3 - Повторение",
				window_width / 2, window_height / 2 + font_size / 2 + line_spacing / 2,
				255, 255, 255,
				1, 1
			);

			draw_text_line(
				renderer,
				font,
				"0 - Выбор букварей",
				window_width / 2, window_height - 4 * line_spacing - font_size,
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

			draw_y_pos = line_spacing * 3 + font_size;
			draw_x_pos = line_spacing * 3;

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
			draw_x_pos = window_width - line_spacing * 3;

			for (int i = 0; i < DIGIT_primer_lenght; i++) {
				draw_text_line(
					renderer,
					font,
					DIGIT_primer[i].letter,
					draw_x_pos - 50 - font_size, draw_y_pos - scroll_offset,
					255, 255, 255,
					2, 0
				);

				draw_text_line(
					renderer,
					font,
					DIGIT_primer[i].code,
					draw_x_pos, draw_y_pos - scroll_offset,
					255, 255, 255,
					2, 0
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
					draw_x_pos - 50 - font_size, draw_y_pos - scroll_offset,
					255, 255, 255,
					2, 0
				);

				draw_text_line(
					renderer,
					font,
					PUNCTUATION_primer[i].code,
					draw_x_pos, draw_y_pos - scroll_offset,
					255, 255, 255,
					2, 0
				);

				draw_y_pos += line_spacing + font_size;
			}

			// Разделительные полосы

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			
			SDL_RenderDrawLine(
				renderer,
				window_width / 3, 0,
				window_width / 3, window_height
			);
			SDL_RenderDrawLine(
				renderer,
				window_width * 2 / 3, 0,
				window_width * 2 / 3, window_height
			);

		}
		else if (scene == "Изучение") {

			// Отрисовка основной информации

			draw_text_line(
				renderer,
				giant_font,
				pair_to_learn[training_stage % pair_to_learn_count].letter,
				window_width / 2, window_height / 2,
				255, 255, 255,
				1, 1
			);
			if (training_stage < pair_to_learn_count) draw_text_line(
				renderer,
				giant_font,
				pair_to_learn[training_stage % pair_to_learn_count].code,
				window_width / 2, window_height / 2 - giant_font_size,
				255, 255, 255,
				1, 1
			);

			draw_text_line(
				renderer,
				giant_font,
				input_code,
				window_width / 2, window_height / 2 + giant_font_size,
				50, 200, 200,
				1, 1
			);

			// Логика проверки ответа

			int code_is_correct = 1;
			int has_spell_mistake = 0;

			for (int i = 0; i < strlen(pair_to_learn[training_stage % pair_to_learn_count].code); i++) {
				if (input_code[i] != pair_to_learn[training_stage % pair_to_learn_count].code[i]) {
					if (input_code[i] != '\0') has_spell_mistake = 1;

					code_is_correct = 0;
					break;
				}
			}
			if(input_code[strlen(pair_to_learn[training_stage % pair_to_learn_count].code)] != '\0') has_spell_mistake = 0;

			if (code_is_correct) {
				input_index = 0;
				for (int i = 0; i < input_code_lenght; i++) input_code[i] = '\0';
				
				training_stage++;
			}
			else if (has_spell_mistake) {
				mistakes_counter++;

				input_index = 0;
				for (int i = 0; i < input_code_lenght; i++) input_code[i] = '\0';
			}

			// Логика завершения режима

			if (training_stage == 2 * pair_to_learn_count) scene = "Результат тренировки";

			// Отрисовка доп. информации

			draw_x_pos = 3 * line_spacing;
			draw_y_pos = 3 * line_spacing;

			for (int i = 0; (i < training_stage) && (i < pair_to_learn_count); i++) {
				draw_text_line(
					renderer,
					font,
					pair_to_learn[i].letter,
					draw_x_pos, draw_y_pos,
					255, 255, 255,
					0, 0
				);
				draw_y_pos += font_size + line_spacing;
			}

			draw_x_pos = 5 * line_spacing + font_size;
			draw_y_pos = 3 * line_spacing;

			for (int i = 0; i < training_stage - pair_to_learn_count; i++) {
				draw_text_line(
					renderer,
					font,
					pair_to_learn[i].code,
					draw_x_pos, draw_y_pos,
					255, 255, 255,
					0, 0
				);
				draw_y_pos += font_size + line_spacing;
			}

			snprintf(buffer_for_int_as_string, sizeof(buffer_for_int_as_string), "Количество ошибок: %d", mistakes_counter);
			draw_text_line(
				renderer,
				font,
				buffer_for_int_as_string,
				window_width - 3 * line_spacing, 3 * line_spacing,
				255, 255, 255,
				2, 0
			);

		}

		else if (scene == "Результат тренировки") {

			snprintf(buffer_for_int_as_string, sizeof(buffer_for_int_as_string), "Всего ошибок: %d", mistakes_counter);
			draw_text_line(
				renderer,
				font,
				buffer_for_int_as_string,
				window_width / 2, window_height / 2,
				255, 255, 255,
				1, 1
			);

		}

		else if (scene == "Выбор букварей") {
			
			draw_text_line(
				renderer,
				font,
				"Выбор букварей",
				window_width / 2, line_spacing,
				255, 255, 255,
				1, 0
			);

			draw_text_line(
				renderer,
				font,
				"E - Английски букварь",
				window_width / 2, window_height / 2 - font_size * 3 / 2 - line_spacing * 3 / 2,
				255, 255, 255,
				1, 1
			);
			if (primer_status.EN) {
				draw_checkmark(
					renderer,
					window_width / 4, window_height / 2 - font_size * 3 / 2 - line_spacing * 3 / 2,
					font_size * 2 / 3, font_size / 10,
					100, 255, 100,
					1, 1
				);
				draw_checkmark(
					renderer,
					3 * window_width / 4, window_height / 2 - font_size * 3 / 2 - line_spacing * 3 / 2,
					font_size * 2 / 3, font_size / 10,
					100, 255, 100,
					1, 1
				);
			}
			else {
				draw_cross(
					renderer,
					window_width / 4, window_height / 2 - font_size * 3 / 2 - line_spacing * 3 / 2,
					font_size * 2 / 3, font_size / 10,
					255, 100, 100,
					1, 1
				);
				draw_cross(
					renderer,
					3 * window_width / 4, window_height / 2 - font_size * 3 / 2 - line_spacing * 3 / 2,
					font_size * 2 / 3, font_size / 10,
					255, 100, 100,
					1, 1
				);
			}

			draw_text_line(
				renderer,
				font,
				"R - Русский букварь",
				window_width / 2, window_height / 2 - font_size  / 2 - line_spacing / 2,
				255, 255, 255,
				1, 1
			);
			if (primer_status.RU) {
				draw_checkmark(
					renderer,
					window_width / 4, window_height / 2 - font_size / 2 - line_spacing / 2,
					font_size * 2 / 3, font_size / 10,
					100, 255, 100,
					1, 1
				);
				draw_checkmark(
					renderer,
					3 * window_width / 4, window_height / 2 - font_size / 2 - line_spacing / 2,
					font_size * 2 / 3, font_size / 10,
					100, 255, 100,
					1, 1
				);
			}
			else {
				draw_cross(
					renderer,
					window_width / 4, window_height / 2 - font_size / 2 - line_spacing / 2,
					font_size * 2 / 3, font_size / 10,
					255, 100, 100,
					1, 1
				);
				draw_cross(
					renderer,
					3 * window_width / 4, window_height / 2 - font_size / 2 - line_spacing / 2,
					font_size * 2 / 3, font_size / 10,
					255, 100, 100,
					1, 1
				);
			}

			draw_text_line(
				renderer,
				font,
				"D - Цифровой букварь",
				window_width / 2, window_height / 2 + font_size / 2 + line_spacing / 2,
				255, 255, 255,
				1, 1
			);
			if (primer_status.DIGIT) {
				draw_checkmark(
					renderer,
					window_width / 4, window_height / 2 + font_size / 2 + line_spacing / 2,
					font_size * 2 / 3, font_size / 10,
					100, 255, 100,
					1, 1
				);
				draw_checkmark(
					renderer,
					3 * window_width / 4, window_height / 2 + font_size / 2 + line_spacing / 2,
					font_size * 2 / 3, font_size / 10,
					100, 255, 100,
					1, 1
				);
			}
			else {
				draw_cross(
					renderer,
					window_width / 4, window_height / 2 + font_size / 2 + line_spacing / 2,
					font_size * 2 / 3, font_size / 10,
					255, 100, 100,
					1, 1
				);
				draw_cross(
					renderer,
					3 * window_width / 4, window_height / 2 + font_size / 2 + line_spacing / 2,
					font_size * 2 / 3, font_size / 10,
					255, 100, 100,
					1, 1
				);
			}

			draw_text_line(
				renderer,
				font,
				"P - Пунктуационный букварь",
				window_width / 2, window_height / 2 + font_size * 3 / 2 + line_spacing * 3 / 2,
				255, 255, 255,
				1, 1
			);
			if (primer_status.PUNCTUATION) {
				draw_checkmark(
					renderer,
					window_width / 4, window_height / 2 + font_size * 3 / 2 + line_spacing * 3 / 2,
					font_size * 2 / 3, font_size / 10,
					100, 255, 100,
					1, 1
				);
				draw_checkmark(
					renderer,
					3 * window_width / 4, window_height / 2 + font_size * 3 / 2 + line_spacing * 3 / 2,
					font_size * 2 / 3, font_size / 10,
					100, 255, 100,
					1, 1
				);
			}
			else {
				draw_cross(
					renderer,
					window_width / 4, window_height / 2 + font_size * 3 / 2 + line_spacing * 3 / 2,
					font_size * 2 / 3, font_size / 10,
					255, 100, 100,
					1, 1
				);
				draw_cross(
					renderer,
					3 * window_width / 4, window_height / 2 + font_size * 3 / 2 + line_spacing * 3 / 2,
					font_size * 2 / 3, font_size / 10,
					255, 100, 100,
					1, 1
				);
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