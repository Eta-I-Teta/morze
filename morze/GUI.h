#pragma once

#include <string.h>

#include <SDL.h>
#include <SDL_ttf.h>


/*
¬ыводит одну текстовую строку в указанную позицию на экране с заданным цветом

@param renderer - ”казатель на SDL_Renderer, в который будет произведена отрисовка
@param font - ”казатель на загруженный TTF_Font
@param text - ”казатель на строку
@param x - ѕоложение текста по горизонтали (в пиксел€х)
@param y - ѕоложение текста по вертикали (в пиксел€х)
@param r -  расна€ компонента цвета (0Ц255)
@param g - «елЄна€ компонента цвета (0Ц255)
@param b - —ин€€ компонента цвета (0Ц255)
@param horizontal_align - √оризонтальное выравнивание: 0 Ч левый край, 1 Ч центр, 2 Ч правый край
@param vertical_align - ¬ертикальное выравнивание: 0 Ч верхний край, 1 Ч центр, 2 Ч нижний край
*/
void draw_text_line(
    SDL_Renderer* renderer,
    TTF_Font* font,
    const char* text,
    int x, int y,
    Uint8 r, Uint8 g, Uint8 b,
    int horizontal_align,
    int vertical_align
);

/*
–исует крест заданного размера и толщины в указанной позиции с заданным цветом

@param renderer - ”казатель на SDL_Renderer, в который будет произведена отрисовка
@param x - ѕоложение по горизонтали (в пиксел€х)
@param y - ѕоложение по вертикали (в пиксел€х)
@param size - –азмер креста (ширина и высота описанного квадрата в пиксел€х)
@param thickness - “олщина линий
@param r -  расна€ компонента цвета (0Ц255)
@param g - «елЄна€ компонента цвета (0Ц255)
@param b - —ин€€ компонента цвета (0Ц255)
@param horizontal_align - √оризонтальное выравнивание: 0 Ч левый край, 1 Ч центр, 2 Ч правый край
@param vertical_align - ¬ертикальное выравнивание: 0 Ч верхний край, 1 Ч центр, 2 Ч нижний край
*/
void draw_cross(
	SDL_Renderer* renderer,
	int x, int y,
	int size,
	int thickness,
	Uint8 r, Uint8 g, Uint8 b,
	int horizontal_align,
	int vertical_align
);

/*
–исует галочку заданного размера и толщины в указанной позиции с заданным цветом

@param renderer - ”казатель на SDL_Renderer, в который будет произведена отрисовка
@param x - ѕоложение по горизонтали (в пиксел€х)
@param y - ѕоложение по вертикали (в пиксел€х)
@param size - –азмер галочки (ширина и высота описанного квадрата в пиксел€х)
@param thickness - “олщина линий
@param r -  расна€ компонента цвета (0Ц255)
@param g - «елЄна€ компонента цвета (0Ц255)
@param b - —ин€€ компонента цвета (0Ц255)
@param horizontal_align - √оризонтальное выравнивание: 0 Ч левый край, 1 Ч центр, 2 Ч правый край
@param vertical_align - ¬ертикальное выравнивание: 0 Ч верхний край, 1 Ч центр, 2 Ч нижний край
*/
void draw_checkmark(
	SDL_Renderer* renderer,
	int x, int y,
	int size,
	int thickness,
	Uint8 r, Uint8 g, Uint8 b,
	int horizontal_align,
	int vertical_align
);