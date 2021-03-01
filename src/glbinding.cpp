#include <rt/loader.hpp>

namespace rt {
	bool load(glloader loader) {
		glbinding::Binding::initialize(loader);
		return true;
	}

	bool load() {
		glbinding::Binding::initialize(glbinding::getProcAddress);
		return false;
	};
};