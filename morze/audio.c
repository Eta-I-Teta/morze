#include <stdio.h>

#include <SDL.h>

#include "audio.h"

SDL_AudioDeviceID audio_dev = 0;
short* beep_buffer = NULL;
int beep_samples = 0;

void start_beep(const int frequency) {

    // Предварительная настройка

    if (audio_dev) return;

    const int rate = 22050, duration = 5000;
    beep_samples = (rate * duration) / 1000;

    beep_buffer = malloc(beep_samples * sizeof(short));
    if (beep_buffer == NULL) {
        printf("Выполнение программы невозможно: Ошибка выделения памяти (beep_buffer)");
        return;
    }

    for (int i = 0; i < beep_samples; i++) {
        double t = (double)i / rate;
        beep_buffer[i] = (short)(16000 * sin(2 * M_PI * frequency * t));
    }

    // Настройка аудиоустройства

    SDL_AudioSpec want = { 0 };
    want.freq = rate;
    want.format = AUDIO_S16LSB;
    want.channels = 1;
    want.samples = 1024;

    audio_dev = SDL_OpenAudioDevice(NULL, 0, &want, NULL, 0);

    // Вопсроизведение звука

    if (audio_dev) {
        SDL_QueueAudio(audio_dev, beep_buffer, beep_samples * sizeof(short));
        SDL_PauseAudioDevice(audio_dev, 0);
    }
    else {
        printf("Выполнение программы невозможно: Ошибка инициализации аудиоустройства (audio_dev)");
        return;
    }
}

void stop_beep() {
    if (audio_dev) {
        SDL_CloseAudioDevice(audio_dev);
        audio_dev = 0;
        free(beep_buffer);
        beep_buffer = NULL;
    }
}

void beep(const int frequency, const int duration) {
    start_beep(frequency);
    SDL_Delay(duration);
    stop_beep();
}