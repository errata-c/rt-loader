# ez-glcompat

Simple configuration library for using OpenGL with a loader of your choosing.
Link to your opengl loading library and then use the abstraction provided.

```c++
#include <ez/gl.h>

int main(int, const char **) {
	// Required to be compatible with most opengl loaders.
	ez::gl::load();

	GLuint id = 0;
	glCreateBuffers(1, &id);
	glDestroyBuffers(1, &id);

	ez::gl::unload();
	return 0;
}
```