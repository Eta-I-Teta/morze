#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

#include "morse_alphabet.h"

const LettersPair EN_primer[] = {
    {"A", ".-"},     {"B", "-..."},   {"C", "-.-."},   {"D", "-.."},
    {"E", "."},      {"F", "..-."},   {"G", "--."},    {"H", "...."},
    {"I", ".."},     {"J", ".---"},   {"K", "-.-"},    {"L", ".-.."},
    {"M", "--"},     {"N", "-."},     {"O", "---"},    {"P", ".--."},
    {"Q", "--.-"},   {"R", ".-."},    {"S", "..."},    {"T", "-"},
    {"U", "..-"},    {"V", "...-"},   {"W", ".--"},    {"X", "-..-"},
    {"Y", "-.--"},   {"Z", "--.."}
};
const int EN_primer_lenght = sizeof(EN_primer) / sizeof(EN_primer[0]);

const LettersPair RU_primer[] = {
    {"А", ".-"},     {"Б", "-..."},   {"В", ".--"},    {"Г", "--."},
    {"Д", "-.."},    {"Е", "."},      {"Ё", ".-..-."}, {"Ж", "...-"},
    {"З", "--.."},   {"И", ".."},     {"Й", ".---"},   {"К", "-.-"},
    {"Л", ".-.."},   {"М", "--"},     {"Н", "-."},     {"О", "---"},
    {"П", ".--."},   {"Р", ".-."},    {"С", "..."},    {"Т", "-"},
    {"У", "..-"},    {"Ф", "..-."},   {"Х", "...."},   {"Ц", "-.-."},
    {"Ч", "---."},   {"Ш", "----"},   {"Щ", "--.-"},   {"Ъ", "--.--"},
    {"Ы", "-.--"},   {"Ь", "..-.."},  {"Э", "..-.."},  {"Ю", "..--"},
    {"Я", ".-.-"}
};
const int RU_primer_lenght = sizeof(RU_primer) / sizeof(RU_primer[0]);

const LettersPair DIGIT_primer[] = {
    {"0", "-----"},  {"1", ".----"},  {"2", "..---"},  {"3", "...--"},
    {"4", "....-"},  {"5", "....."},  {"6", "-...."},  {"7", "--..."},
    {"8", "---.."},  {"9", "----."}
};
const int DIGIT_primer_lenght = sizeof(DIGIT_primer) / sizeof(DIGIT_primer[0]);

const LettersPair PUNCTUATION_primer[] = {
    {".", ".-.-.-"}, {",", "--..--"}, {"?", "..--.."}, {"!", "-.-.--"},
    {"(", "-.--."},  {")", "-.--.-"}, {":", "---..."}, {"-", "-....-"},
    {"'", ".-..-."}
};
const int PUNCTUATION_primer_lenght = sizeof(PUNCTUATION_primer) / sizeof(PUNCTUATION_primer[0]);

//char* code_to_letters(char* code) {
//    char* str = malloc(100 * sizeof(char));
//    assert(str != NULL);
//
//
//}

//char* read_morse_letter() {
//    char* letter = malloc(7 * sizeof(char));
//    assert(letter != NULL);
//
//    char symbol;
//    int index = 0;
//
//    letter[0] = '\0';
//
//    int idle_time = 0;
//
//    while (1) {
//        // Space
//        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
//            DWORD start = GetTickCount64();
//
//            while (GetAsyncKeyState(VK_SPACE) & 0x8000) Sleep(10);
//
//            DWORD held = GetTickCount64() - start;
//
//            if (held < 10) continue;
//            else if (held < DOT_THRESHOLD) symbol = '.';
//            else symbol = '-';
//
//            letter[index++] = symbol;
//            letter[index] = '\0';
//
//            idle_time = 0;
//        }
//
//        // return
//        else if ((idle_time > LETTER_THRESHOLD) || (index >= 7)) return letter;
//
//        else idle_time += 10;
//
//        Sleep(10);
//    }
//}