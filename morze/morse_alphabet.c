#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

#include "morse_alphabet.h"

//char* code_to_letters(char* code) {
//    char* str = malloc(100 * sizeof(char));
//    assert(str != NULL);
//
//
//}

char* read_morse_letter() {
    char* letter = malloc(7 * sizeof(char));
    assert(letter != NULL);

    char symbol;
    int index = 0;

    letter[0] = '\0';

    int idle_time = 0;

    while (1) {
        // Space
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            DWORD start = GetTickCount64();

            while (GetAsyncKeyState(VK_SPACE) & 0x8000) Sleep(10);

            DWORD held = GetTickCount64() - start;

            if (held < 10) continue;
            else if (held < DOT_THRESHOLD) symbol = '.';
            else symbol = '-';

            letter[index++] = symbol;
            letter[index] = '\0';

            idle_time = 0;
        }

        // return
        else if ((idle_time > LETTER_THRESHOLD) || (index >= 7)) return letter;

        else idle_time += 10;

        Sleep(10);
    }
}