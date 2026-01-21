#pragma once

#include "training.h"
#include "other_settings.h"
#include "morse_alphabet.h"

void save_other_settings(OtherSettings* other_settings, TrainingState* training_state);
void load_other_settings(OtherSettings* other_settings, TrainingState* training_state);

void save_primer_status(PrimerStatus* primer_status);