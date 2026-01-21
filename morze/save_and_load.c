#if _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include <stdio.h>
#include <string.h>

#include "save_and_load.h"

char load_buffer[128];

char key[64];
int value;

void save_other_settings(OtherSettings* other_settings, TrainingState* training_state) {
	FILE* file = fopen("config/other_settings.cfg", "w+");
	if (file == NULL) {
		printf("Не удалось открыть файл (other_settings.cfg)");
		return;
	}

	fprintf(file, "DOT_THRESHOLD %d\n", other_settings->DOT_THRESHOLD);
	fprintf(file, "is_mute %d\n", other_settings->is_mute);
	fprintf(file, "frequency %d\n", other_settings->frequency);

	fprintf(file, "pair_to_learn_count %d\n", training_state->pair_to_learn_count);

	fclose(file);
}

void load_other_settings(OtherSettings* other_settings, TrainingState* training_state) {
	FILE* file = fopen("config/other_settings.cfg", "r");
	if (file == NULL) {
		printf("Не удалось открыть файл (other_settings.cfg)");
		return;
	}

	while (fgets(load_buffer, sizeof(load_buffer), file)) {
		if (load_buffer[0] == '\0') continue;

		if (sscanf_s(load_buffer, "%63[^=]=%d", key, (unsigned)(sizeof(key) / sizeof(load_buffer[0])), &value) == 2) {
			
			if (key == "DOT_THRESHOLD") other_settings->DOT_THRESHOLD = value;
			else if (key == "is_mute") other_settings->is_mute = value;
			else if (key == "frequency") other_settings->frequency = value;

			else if (key == "pair_to_learn_count") training_state->pair_to_learn_count = value;

			else {
				printf("Ошибка целостности файла (other_settings.cfg)");
				return;
			}

		}
		else {
			printf("Ошибка чтения данных из файла (other_settings.cfg)");
			return;
		}
	}

	fclose(file);
}

void save_primer_status(PrimerStatus* primer_status) {
	FILE* file = fopen("config/primer_status.cfg", "w+");
	if (file == NULL) {
		printf("Не удалось открыть файл (primer_status.cfg)");
		return;
	}

	fprintf(file, "EN %d\n", primer_status->EN);
	fprintf(file, "RU %d\n", primer_status->RU);
	fprintf(file, "DIGIT %d\n", primer_status->DIGIT);
	fprintf(file, "PUNCTUATION %d\n", primer_status->PUNCTUATION);

	fclose(file);
}