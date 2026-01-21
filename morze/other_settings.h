#pragma once

typedef struct {
	int DOT_THRESHOLD;
	int is_mute;
} OtherSettings;

OtherSettings* create_other_settings();