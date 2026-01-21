#pragma once

/*
Запускает непрерывный тональный звук заданной частоты на аудиовыходе

@param frequency — частота звукового сигнала в герцах
*/
void start_beep(const int frequency);

/*
Немедленно останавливает текущее воспроизведение звука и освобождает выделенные ресурсы
*/
void stop_beep();


void beep(const int frequency, const int duration);