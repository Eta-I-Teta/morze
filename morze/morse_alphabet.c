#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <assert.h>
#include <time.h>

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


/*
Возвращает случайную пару "символ – код Морзе" (LettersPair) из латинского алфавита
Предполагает, что генератор случайных чисел уже инициализирован (srand)
*/
static LettersPair get_random_EN_pair() {
	int index = rand() % EN_primer_lenght;
	return EN_primer[index];
}
/*
Возвращает случайную пару "символ – код Морзе" (LettersPair) из кириллицы
Предполагает, что генератор случайных чисел уже инициализирован (srand)
*/
static LettersPair get_random_RU_pair() {
	int index = rand() % RU_primer_lenght;
	return RU_primer[index];
}
/*
Возвращает случайную пару "символ – код Морзе" (LettersPair) из цифр
Предполагает, что генератор случайных чисел уже инициализирован (srand)
*/
static LettersPair get_random_DIGIT_pair() {
	int index = rand() % DIGIT_primer_lenght;
	return DIGIT_primer[index];
}
/*
Возвращает случайную пару "символ – код Морзе" (LettersPair) из знаков пунктуации
Предполагает, что генератор случайных чисел уже инициализирован (srand)
*/
static LettersPair get_random_PUNCTUATION_pair() {
	int index = rand() % PUNCTUATION_primer_lenght;
	return PUNCTUATION_primer[index];
}

LettersPair get_random_pair() {
	int primer_ID;

	while (1) {
		primer_ID = rand() % 4;

		if ((primer_ID == 0) && (primer_status.EN)) return get_random_EN_pair();
		else if ((primer_ID == 1) && (primer_status.RU)) return get_random_RU_pair();
		else if ((primer_ID == 2) && (primer_status.DIGIT)) return get_random_DIGIT_pair();
		else if ((primer_ID == 3) && (primer_status.PUNCTUATION)) return get_random_PUNCTUATION_pair();

		else if (!primer_status.EN && 
				 !primer_status.RU && 
				 !primer_status.DIGIT && 
				 !primer_status.PUNCTUATION) return get_random_PUNCTUATION_pair();
	}
}