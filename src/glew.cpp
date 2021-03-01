#include <rt/loader.hpp>

namespace rt {
	bool load() {
		int err = glewInit();
		return err == GLEW_OK;
	};

	bool load(glloader loader) {
		return load();
	};
};
