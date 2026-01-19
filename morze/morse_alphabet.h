#pragma once

#define DOT_THRESHOLD 150

typedef struct {
    char* letter;
    char* code;
} LettersPair;

extern const LettersPair EN_primer[];
extern const int EN_primer_lenght;

extern const LettersPair RU_primer[];
extern const int RU_primer_lenght;

extern const LettersPair DIGIT_primer[];
extern const int DIGIT_primer_lenght;

extern const LettersPair PUNCTUATION_primer[];
extern const int PUNCTUATION_primer_lenght;

typedef struct {
    int EN;
    int RU;
    int DIGIT;
    int PUNCTUATION;
} PrimerStatus;

extern PrimerStatus primer_status;

/*
Возвращает случайную пару "символ – код Морзе", выбирая из доступных наборов
Выбор осуществляется только среди тех наборов, которые включены в primer_status
*/
LettersPair get_random_pair();