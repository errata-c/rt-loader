#include <rt/loader.hpp>

bool rt_loader_load(void) {
	return gladLoadGL() == 0;
};

bool rt_loader_load_with(rt_loader_glloader loader) {
	return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(loader)) == 0;
};