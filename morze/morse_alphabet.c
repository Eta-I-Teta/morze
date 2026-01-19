#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

#include "morse_alphabet.h"

#if _MSC_VER
#pragma execution_character_set("utf-8")
#endif

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
    {"\"", ".-..-."}
};
const int PUNCTUATION_primer_lenght = sizeof(PUNCTUATION_primer) / sizeof(PUNCTUATION_primer[0]);

PrimerStatus primer_status = { 0, 1, 0, 0 };