#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "training.h"

/*
Отрисовывает текущую сцену интерфейса тренажёра Морзе в зависимости от переданных аттрибутов

@param renderer - Указатель на SDL_Renderer для отрисовки
@param scene - Текущая сцена (строка с названием)
@param font - Основной шрифт для текста
@param font_size - Размер основного шрифта (в пикселях)
@param giant_font - Крупный шрифт для отображения символов
@param giant_font_size - Размер крупного шрифта (в пикселях)
@param line_spacing - Вертикальный отступ между строками (в пикселях)
@param window_width - Ширина окна (в пикселях)
@param window_height - Высота окна (в пикселях)
@param scroll_offset - Смещение прокрутки
@param training_state - Указатель на состояние тренировки (ввод, ошибки, прогресс и т.д.)

@return Возвращает указатель на текущую сцену (может быть изменён внутри функции)
*/
char* draw_scene(

	SDL_Renderer* renderer,
	char* scene,

	TTF_Font* font, int font_size,
	TTF_Font* giant_font, int giant_font_size,
	int line_spacing,

	int window_width, int window_height,
	int scroll_offset,

	TrainingState* training_state

);