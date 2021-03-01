
string(TOLOWER "${rt-loader_FIND_COMPONENTS}" "COMPS")

# Glew component requested, and glew target does not exist
if("glew" IN_LIST "COMPS" AND (NOT TARGET GLEW::GLEW))
	find_dependency(GLEW CONFIG)
endif()

# Glad component requested, and glad target does not exist
if("glad" IN_LIST "COMPS" AND (NOT TARGET glad::glad))
	find_dependency("glad" CONFIG)
endif()

# gl3w component requested, and glew target does not exist
if("gl3w" IN_LIST "COMPS" AND (NOT TARGET unofficial::gl3w::gl3w))
	find_dependency("gl3w" CONFIG)
endif()

# Glbinding component requested, and glew target does not exist
if("glbinding" IN_LIST "COMPS" AND (NOT TARGET glbinding::glbinding))
	find_dependency("glbinding" CONFIG)
endif()

