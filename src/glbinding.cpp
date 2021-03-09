#include <rt/loader.hpp>

bool rt_loader_load(void) {
	glbinding::Binding::initialize(glbinding::getProcAddress);
	return true;
};

bool rt_loader_load_with(rt_loader_glloader loader) {
	glbinding::Binding::initialize((rt::glloader)loader);
	return true;
};
