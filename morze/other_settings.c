#include <stdio.h>
#include <stdlib.h>

#include "other_settings.h"

OtherSettings* create_other_settings() {
	OtherSettings* other_settings = malloc(sizeof(OtherSettings));
	if (other_settings == NULL) printf("Выполнение программы невозможно: Ошибка выделения памяти (other_settings)");
	else {
		other_settings->DOT_THRESHOLD = 250;
		other_settings->is_mute = 0;
		other_settings->frequency = 800;
	}

	return other_settings;
}