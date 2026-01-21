#pragma once

typedef struct {
	int DOT_THRESHOLD;
	int is_mute;
	int frequency;
} OtherSettings;

/*
—оздаЄт и инициализирует структуру прочих настроек программы по умолчанию.

@return ”казатель на созданную структуру OtherSettings, или NULL в случае нехватки пам€ти
*/
OtherSettings* create_other_settings();