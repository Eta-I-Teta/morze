#pragma once

#include "training.h"
#include "other_settings.h"
#include "morse_alphabet.h"

/*
—охран€ет прочие настройки программы и состо€ние тренировки в конфигурационный файл

@param other_settings Ч указатель на структуру с прочими настройками
@param training_state Ч указатель на структуру состо€ни€ тренировки
*/
void save_other_settings(OtherSettings* other_settings, TrainingState* training_state);
/*
«агружает прочие настройки программы и состо€ние тренировки из конфигурационного файла

@param other_settings Ч указатель на структуру с прочими настройками
@param training_state Ч указатель на структуру состо€ни€ тренировки
*/
void load_other_settings(OtherSettings* other_settings, TrainingState* training_state);


/*
—охран€ет состо€ние активных букварей в конфигурационный файл

@param primer_status Ч указатель на структуру состо€ни€ букварей
*/
void save_primer_status(PrimerStatus* primer_status);
/*
«агружает состо€ние активных букварей из конфигурационного файла

@param primer_status Ч указатель на структуру состо€ни€ букварей
*/
void load_primer_status(PrimerStatus* primer_status);


/*
—брасывает прочие настройки программы и параметры тренировки к значени€м по умолчанию

@param other_settings Ч указатель на структуру с общими настройками программы
@param training_state Ч указатель на структуру состо€ни€ тренировки
*/
void reset_other_settings(OtherSettings* other_settings, TrainingState* training_state);