#include <rt/loader.hpp>

bool rt_loader_load(void) {
	return gl3wInit() == 0;
};

bool rt_loader_load_with(rt_loader_glloader loader) {
	return gl3wInit() == 0;
};