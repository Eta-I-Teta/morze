#include "scene.h"

void scene_change(Scene* new_scene, Scene* global_scene_var, int* scroll_offset, int* max_scroll_offset) {
	global_scene_var = new_scene;

	scroll_offset = (int*)0;
	max_scroll_offset = (int*)global_scene_var->max_scroll_offset;
}