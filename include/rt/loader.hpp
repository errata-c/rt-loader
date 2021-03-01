#pragma once
namespace rt {
	namespace intern {
		static constexpr int numGLLibs = 0
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
			;
	};
};

static_assert(rt::intern::numGLLibs != 0, "No supported OpenGL loader library found!");
static_assert(rt::intern::numGLLibs == 1, "Too many OpenGL loader libraries found!");

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

namespace rt {
	using glproc = void(*)(void);
	using glloader = glproc(*)(const char*);

	bool load();
	bool load(glloader loader);
};