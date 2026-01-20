
#include <SDL.h>

#include "audio.h"

void play_beep(int duration_ms, int frequency) {
    const int SAMPLE_RATE = 22050;
    const int NUM_SAMPLES = (SAMPLE_RATE * duration_ms) / 1000;

    // Открываем аудиоустройство
    SDL_AudioSpec spec;
    spec.freq = SAMPLE_RATE;
    spec.format = AUDIO_S16LSB;
    spec.channels = 1;        // моно
    spec.samples = 1024;
    spec.callback = NULL;

    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
    if (dev == 0) return; // если не получилось — выходим

    // Генерируем синусоиду
    short* buffer = (short*)malloc(NUM_SAMPLES * sizeof(short));
    for (int i = 0; i < NUM_SAMPLES; i++) {
        double t = (double)i / SAMPLE_RATE;
        buffer[i] = (short)(16000.0 * sin(2.0 * M_PI * frequency * t));
    }

    // Воспроизводим
    SDL_QueueAudio(dev, buffer, NUM_SAMPLES * sizeof(short));
    SDL_PauseAudioDevice(dev, 0); // запуск
    SDL_Delay(duration_ms);  // ждём окончания

    // Очистка
    free(buffer);
    SDL_CloseAudioDevice(dev);
}