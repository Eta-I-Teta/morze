#include <string.h>
#include "training.h"

void clear_input(TrainingState* training_state) {
	training_state->input_index = 0;

	for (int i = 0; i < training_state->input_code_lenght; i++) training_state->input_code[i] = '\0';
}

void update_pair_to_learn(TrainingState* training_state) {
	for (int i = 0; i < training_state->pair_to_learn_count; i++) training_state->pair_to_learn[i] = get_random_pair();
}

void init_training_state(TrainingState* training_state) {
	training_state->input_code_lenght = sizeof(training_state->input_code) / sizeof(training_state->input_code[0]) - 1;
	training_state->input_index = 0;

	clear_input(training_state);
	training_state->input_code[training_state->input_code_lenght] = '\0';

	training_state->mistakes = 0;
	training_state->stage = 0;

	training_state->pair_to_learn_count = 3;
}

int check_answer(TrainingState* training_state) {
	char* needed_code = training_state->pair_to_learn[training_state->stage % training_state->pair_to_learn_count].code;
	
	int code_is_correct = 1;

	for (int i = 0; i < strlen(needed_code); i++) {

		if (training_state->input_code[i] != needed_code[i]) {
			if (training_state->input_code[i] != '\0') {
				training_state->mistakes++;
				clear_input(training_state);
			}
			
			code_is_correct = 0;
			break;
		}

	}

	if (code_is_correct) {
		clear_input(training_state);
		training_state->stage++;

		return 1;
	}

	return 0;
}