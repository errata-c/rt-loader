#include <rt/loader.hpp>

bool rt_loader_load(void) {
	int err = glewInit();
	return err == GLEW_OK;
};
bool rt_loader_load_with(rt_loader_glloader loader) {
	return rt_loader_load();
};
