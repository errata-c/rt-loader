# rt-loader

Simple configuration library for using OpenGL with a loader of your choosing.
Link to the appropriate component and call `rt::load()`

CMake
```cmake
find_package(rt-loader CONFIG REQUIRED COMPONENTS glew)

target_link_libraries(foo PRIVATE rt::loader-glew)
```

C++
```c++
#include <rt/loader.hpp>

int main(int, const char **) {
	// Required to be compatible with most opengl loaders.
	rt::load();

	GLuint id = 0;
	glCreateBuffers(1, &id);
	glDestroyBuffers(1, &id);
	
	return 0;
}
```