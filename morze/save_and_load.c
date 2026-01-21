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
	fprintf(file, "frequency %d\n\n", other_settings->frequency);

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
		if ((load_buffer[0] == '\0')||(load_buffer[0] == '\n')) continue;

		if (sscanf_s(load_buffer, "%64[^ ]%d", key, (unsigned)(sizeof(key) / sizeof(load_buffer[0])), &value) == 2) {
			
			if (strcmp(key, "DOT_THRESHOLD") == 0) other_settings->DOT_THRESHOLD = value;
			else if (strcmp(key, "is_mute") == 0) other_settings->is_mute = value;
			else if (strcmp(key, "frequency") == 0) other_settings->frequency = value;

			else if (strcmp(key, "pair_to_learn_count") == 0) training_state->pair_to_learn_count = value;

			else {
				printf("Ошибка целостности файла (other_settings.cfg)\n");
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

void load_primer_status(PrimerStatus* primer_status) {
	FILE* file = fopen("config/primer_status.cfg", "r");
	if (file == NULL) {
		printf("Не удалось открыть файл (primer_status.cfg)");
		return;
	}

	while (fgets(load_buffer, sizeof(load_buffer), file)) {
		if ((load_buffer[0] == '\0') || (load_buffer[0] == '\n')) continue;

		if (sscanf_s(load_buffer, "%63[^ ]%d", key, (unsigned)(sizeof(key) / sizeof(load_buffer[0])), &value) == 2) {

			if (strcmp(key, "EN") == 0) primer_status->EN = value;
			else if (strcmp(key, "RU") == 0) primer_status->RU = value;
			else if (strcmp(key, "DIGIT") == 0) primer_status->DIGIT = value;
			else if (strcmp(key, "PUNCTUATION") == 0) primer_status->PUNCTUATION = value;

			else {
				printf("Ошибка целостности файла (primer_status.cfg)\n");
				return;
			}

		}
		else {
			printf("Ошибка чтения данных из файла (primer_status.cfg)");
			return;
		}
	}

	fclose(file);
}

void reset_other_settings(OtherSettings* other_settings, TrainingState* training_state) {
	other_settings->DOT_THRESHOLD = 300;
	other_settings->frequency = 800;
	other_settings->is_mute = 0;

	training_state->pair_to_learn_count = 3;
}