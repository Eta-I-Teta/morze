#if _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include <stdio.h>

#include "morse_alphabet.h"
#include "scenes.h"
#include "GUI.h"

char* draw_scene(

	SDL_Renderer* renderer,
	char* scene,

	TTF_Font* font, int font_size,
	TTF_Font* giant_font, int giant_font_size,
	int line_spacing,

	int window_width, int window_height,
	int scroll_offset,

	TrainingState* training_state,

	OtherSettings* other_settings

) {

	char buffer_for_int_as_string[32 + 64];

	int draw_y_pos = 0;
	int draw_x_pos = 0;

	if (scene == "Начальный экран") {
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
	else if (scene == "Выбор режима") {
		draw_text_line(
			renderer,
			font,
			"[1] Азбука Морзе",
			window_width / 2, window_height / 2 - font_size * 5 / 2 - line_spacing * 5 / 2,
			255, 255, 255,
			1, 1
		);
		draw_text_line(
			renderer,
			font,
			"[2] Изучение",
			window_width / 2, window_height / 2 - font_size * 3 / 2 - line_spacing * 3 / 2,
			255, 255, 255,
			1, 1
		);
		draw_text_line(
			renderer,
			font,
			"[3] Повторение",
			window_width / 2, window_height / 2 - font_size / 2 - line_spacing / 2,
			255, 255, 255,
			1, 1
		);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(
			renderer,
			window_width / 4, window_height / 2 + font_size / 2 + line_spacing / 2,
			window_width * 3 / 4, window_height / 2 + font_size / 2 + line_spacing / 2
		);

		draw_text_line(
			renderer,
			font,
			"[9] Выбор букварей",
			window_width / 2, window_height / 2 + font_size * 3 / 2 + line_spacing * 3 / 2,
			255, 255, 255,
			1, 1
		);
		draw_text_line(
			renderer,
			font,
			"[0] Прочие настройки",
			window_width / 2, window_height / 2 + font_size * 5 / 2 + line_spacing * 5 / 2,
			255, 255, 255,
			1, 1
		);

		draw_text_line(
			renderer,
			font,
			"Нажмите цифру, соответствующую номеру режима",
			window_width / 2, window_height - line_spacing * 4 - font_size,
			100, 100, 100,
			1, 1
		);
		draw_text_line(
			renderer,
			font,
			"ESC - выйти",
			window_width / 2, window_height - line_spacing * 3,
			100, 100, 100,
			1, 1
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
			window_width / 3, font_size * 3 / 2,
			window_width / 3, window_height - font_size * 3 / 2
		);
		SDL_RenderDrawLine(
			renderer,
			window_width * 2 / 3, font_size * 3 / 2,
			window_width * 2 / 3, window_height - font_size * 3 / 2
		);

	}
	else if (scene == "Изучение") {

		// Отрисовка основной информации

		LettersPair needed_pair = training_state->pair_to_learn[training_state->stage % training_state->pair_to_learn_count];

		draw_text_line(
			renderer,
			giant_font,
			needed_pair.letter,
			window_width / 2, window_height / 2,
			255, 255, 255,
			1, 1
		);
		if (training_state->stage < training_state->pair_to_learn_count) draw_text_line(
			renderer,
			giant_font,
			needed_pair.code,
			window_width / 2, window_height / 2 - giant_font_size,
			255, 255, 255,
			1, 1
		);

		draw_text_line(
			renderer,
			giant_font,
			training_state->input_code,
			window_width / 2, window_height / 2 + giant_font_size,
			150, 250, 150,
			1, 1
		);

		// Логика проверки ответа

		check_answer(training_state);

		// Логика завершения режима

		if (training_state->stage == 2 * training_state->pair_to_learn_count) scene = "Результат тренировки";

		// Отрисовка доп. информации

		draw_x_pos = 3 * line_spacing;
		draw_y_pos = 3 * line_spacing;

		for (int i = 0; (i < training_state->stage) && (i < training_state->pair_to_learn_count); i++) {
			draw_text_line(
				renderer,
				font,
				training_state->pair_to_learn[i].letter,
				draw_x_pos, draw_y_pos,
				255, 255, 255,
				0, 0
			);
			draw_y_pos += font_size + line_spacing;
		}

		draw_x_pos = 5 * line_spacing + font_size;
		draw_y_pos = 3 * line_spacing;

		for (int i = 0; i < training_state->stage - training_state->pair_to_learn_count; i++) {
			draw_text_line(
				renderer,
				font,
				training_state->pair_to_learn[i].code,
				draw_x_pos, draw_y_pos,
				255, 255, 255,
				0, 0
			);
			draw_y_pos += font_size + line_spacing;
		}

		snprintf(buffer_for_int_as_string, sizeof(buffer_for_int_as_string), "Количество ошибок: %d", training_state->mistakes);
		draw_text_line(
			renderer,
			font,
			buffer_for_int_as_string,
			window_width - 3 * line_spacing, 3 * line_spacing,
			255, 255, 255,
			2, 0
		);

	}
	else if (scene == "Тренировка") {

		// Отрисовка основной информации

		LettersPair needed_pair = training_state->pair_to_learn[training_state->stage % training_state->pair_to_learn_count];

		draw_text_line(
			renderer,
			giant_font,
			needed_pair.letter,
			window_width / 2, window_height / 2,
			255, 255, 255,
			1, 1
		);

		draw_text_line(
			renderer,
			giant_font,
			training_state->input_code,
			window_width / 2, window_height / 2 + giant_font_size,
			150, 150, 250,
			1, 1
		);

		// Логика проверки ответа

		check_answer(training_state);

		// Логика завершения режима

		if (training_state->stage == training_state->pair_to_learn_count) scene = "Результат тренировки";

		// Отрисовка доп. информации

		draw_x_pos = 3 * line_spacing;
		draw_y_pos = 3 * line_spacing;

		for (int i = 0; i < training_state->stage; i++) {
			draw_x_pos = 3 * line_spacing;
			draw_text_line(
				renderer,
				font,
				training_state->pair_to_learn[i].letter,
				draw_x_pos, draw_y_pos,
				255, 255, 255,
				0, 0
			);

			draw_x_pos = 5 * line_spacing + font_size;
			draw_text_line(
				renderer,
				font,
				training_state->pair_to_learn[i].code,
				draw_x_pos, draw_y_pos,
				255, 255, 255,
				0, 0
			);

			draw_y_pos += font_size + line_spacing;
		}

		snprintf(buffer_for_int_as_string, sizeof(buffer_for_int_as_string), "Количество ошибок: %d", training_state->mistakes);
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

		snprintf(buffer_for_int_as_string, sizeof(buffer_for_int_as_string), "Всего ошибок: %d", training_state->mistakes);
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
			window_width / 2, window_height / 2 - font_size / 2 - line_spacing / 2,
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

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(
			renderer,
			window_width / 4, window_height / 2 - (font_size + line_spacing) * 5 / 2,
			window_width * 3 / 4, window_height / 2 - (font_size + line_spacing) * 5 / 2
		);
		SDL_RenderDrawLine(
			renderer,
			window_width / 4, window_height / 2 + (font_size + line_spacing) * 5 / 2,
			window_width * 3 / 4, window_height / 2 + (font_size + line_spacing) * 5 / 2
		);

	}
	else if (scene == "Прочие настройки") {

		draw_text_line(
			renderer,
			font,
			"Прочие настройки",
			window_width / 2, line_spacing,
			255, 255, 255,
			1, 0
		);

		snprintf(buffer_for_int_as_string, sizeof(buffer_for_int_as_string), 
				 "[W/S] Пороговое значение для тире: %d мс", other_settings->DOT_THRESHOLD);
		draw_text_line(
			renderer,
			font,
			buffer_for_int_as_string,
			window_width / 2, window_height / 2,
			255, 255, 255,
			1, 1
		);

		snprintf(buffer_for_int_as_string, sizeof(buffer_for_int_as_string), 
				 "[A/D] Кол-во символов в тренировке: %d", training_state->pair_to_learn_count);
		draw_text_line(
			renderer,
			font,
			buffer_for_int_as_string,
			window_width / 2, window_height / 2 + (font_size + line_spacing),
			255, 255, 255,
			1, 1
		);

		if(other_settings->is_mute) snprintf(buffer_for_int_as_string, sizeof(buffer_for_int_as_string), "[M] Звук: ВЫКЛ");
		else snprintf(buffer_for_int_as_string, sizeof(buffer_for_int_as_string), "[M] Звук: ВКЛ");
		draw_text_line(
			renderer,
			font,
			buffer_for_int_as_string,
			window_width / 2, window_height / 2 + (font_size + line_spacing) * 2,
			255, 255, 255,
			1, 1
		);

		snprintf(buffer_for_int_as_string, sizeof(buffer_for_int_as_string),
			"[E/Q] Тональность сигнала: %d Гц", other_settings->frequency);
		draw_text_line(
			renderer,
			font,
			buffer_for_int_as_string,
			window_width / 2, window_height / 2 + (font_size + line_spacing) * 3,
			255, 255, 255,
			1, 1
		);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(
			renderer,
			window_width / 4, font_size * 3 / 2,
			window_width * 3 / 4, font_size * 3 / 2
		);
		SDL_RenderDrawLine(
			renderer,
			window_width / 4, window_height - font_size * 3 / 2,
			window_width * 3 / 4, window_height - font_size * 3 / 2
		);

	}

	else {
		draw_text_line(
			renderer,
			font,
			"Ошибка идентификации сцены",
			window_width / 2, window_height / 2,
			255, 50, 50,
			1, 1
		);
	}

	return scene;

}