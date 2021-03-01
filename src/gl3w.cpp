#include <rt/loader.hpp>

namespace rt {
	bool load() {
		return gl3wInit() == 0;
	};

	bool load(glloader loader) {
		return load();
	};
};