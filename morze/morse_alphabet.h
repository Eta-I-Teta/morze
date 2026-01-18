#pragma once

#define DOT_THRESHOLD 300  // ms
#define LETTER_THRESHOLD 1000  // ms

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


//char* code_to_letters(char* code);

//char* read_morse_letter();