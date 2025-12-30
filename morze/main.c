#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

#define DOT_THRESHOLD 300  // ms

char* read_morse_code() {
    char word[100];
    char symbol;
    int index = 0;

    word[0] = '\0';

    while (1) {
        // Enter
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            word[index] = '\0';
            return word;
        }

        // Space
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            DWORD start = GetTickCount64();
          
            while (GetAsyncKeyState(VK_SPACE) & 0x8000) Sleep(10);

            DWORD held = GetTickCount64() - start;

            if (held < 10) continue;
            else if (held < DOT_THRESHOLD) symbol = '.';
            else symbol = '-';

            word[index++] = symbol;
        }

        Sleep(10);
    }
}

int main(void) {
	char* locale = setlocale(LC_ALL, "");
	
    char* word = malloc(4 * sizeof(char));
    word = read_morse_code();
    printf("%4s", word);

    free(word);

	return 0;
}