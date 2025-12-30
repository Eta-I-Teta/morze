#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

#include "morse_alphabet.h"



int main(void) {
	char* locale = setlocale(LC_ALL, "");
	
    char* word = malloc(4 * sizeof(char));
    word = read_morse_letter();
    printf("%4s", word);

    free(word);

	return 0;
}