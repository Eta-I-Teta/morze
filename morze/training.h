#pragma once

#include "morse_alphabet.h"

typedef struct {
	int stage;
	int mistakes;

	char input_code[16];
	int input_code_lenght;
	int input_index;

	LettersPair pair_to_learn[3];
	int pair_to_learn_count;
} TrainingState;


/*
Очищает текущий введённый пользователем код Морзе и сбрасывает значение input_index

@param training_state — указатель на структуру состояния тренировки
*/
void clear_input(TrainingState* training_state);

/*
Обновляет массив пар "символ – код Морзе" (pair_to_learn), используемых в текущей тренировке

@param training_state — указатель на структуру состояния тренировки
*/
void update_pair_to_learn(TrainingState* training_state);

/*
Инициализирует состояние тренировки по умолчанию

@param training_state — указатель на структуру состояния тренировки
*/
void init_training_state(TrainingState* training_state);

/*
Проверяет правильность введённого пользователем кода Морзе.

@return 1, если ответ верный; 0 — если неверный.
*/
int check_answer(TrainingState* training_state);