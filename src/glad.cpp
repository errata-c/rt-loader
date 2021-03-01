#include <rt/loader.hpp>

namespace rt {
	bool load(glloader loader) {
		return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(loader)) == 0;
	}

	bool load() {
		return gladLoadGL() == 0;
	};
};