#pragma once
#include <iostream>
#include <functional>

static_assert(0
#if defined(RT_LOADER_GLEW)
	+1
#endif
#if defined(RT_LOADER_GLAD)
	+1
#endif
#if defined(RT_LOADER_GL3W)
	+1
#endif
#if defined(RT_LOADER_GLBINDING)
	+1
#endif
#if defined(RT_LOADER_EPOXY)
	+1
#endif
	<= 1, "Too many OpenGL loaders have been linked!");

extern "C" {
	typedef void (*rt_loader_glproc)(void);
	typedef void*(*rt_loader_glloader)(const char*);

	bool rt_loader_load(void);
	bool rt_loader_load_with(rt_loader_glloader);
}

namespace rt {
	using glproc = rt_loader_glproc;
	using glloader = glproc(*)(const char*);

	using load_function = bool(*)();
	using load_with_function = bool(*)(glloader);

	static bool load() {
		return rt_loader_load();
	}
	static bool load(glloader loader) {
		return rt_loader_load_with((rt_loader_glloader)loader);
	}
};

#if defined(RT_LOADER_GLEW)
#include <GL/glew.h>

#elif defined(RT_LOADER_GL3W)
#include <GL/gl3w.h>

#elif defined(RT_LOADER_GLAD)
#include <glad/glad.h>

#elif defined(RT_LOADER_GLBINDING)
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
#include <glbinding/getProcAddress.h>
using namespace gl;

#elif defined(RT_LOADER_EPOXY)
#include <epoxy/gl.h>

#endif

