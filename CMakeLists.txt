cmake_minimum_required(VERSION 3.15)

project(RT_LOADER
VERSION 0.3.0
LANGUAGES C CXX)

include(GNUInstallDirs)
find_package(ez-cmake CONFIG REQUIRED)

# The five supported loaders will be:
# GLEW, GLEW::GLEW
# glad, glad::glad
# gl3w, unofficial::gl3w::gl3w
# glbinding, glbinding::glbinding
# libepoxy

find_package(glew CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(gl3w CONFIG REQUIRED)
find_package(glbinding CONFIG REQUIRED)

find_path(EPOXY_INCLUDE "epoxy/gl.h")
find_library(EPOXY_LIB "epoxy")

if("${EPOXY_INCLUDE}" STREQUAL "EPOXY_INCLUDE-NOTFOUND")
	message(FATAL_ERROR "Failed to find libepoxy headers!")
endif()

if("${EPOXY_LIB}" STREQUAL "EPOXY_LIB-NOTFOUND")
	message(FATAL_ERROR "Failed to find libepoxy binary!")
endif()

# Create main target.
add_library(rt-loader INTERFACE)
add_library(rt-loader-glew STATIC "src/glew.cpp")
add_library(rt-loader-glad STATIC "src/glad.cpp")
add_library(rt-loader-gl3w STATIC "src/gl3w.cpp")
add_library(rt-loader-glbinding STATIC "src/glbinding.cpp")
add_library(rt-loader-epoxy STATIC "src/epoxy.cpp")

set_target_properties(rt-loader PROPERTIES EXPORT_NAME "loader")
set_target_properties(rt-loader-glew PROPERTIES EXPORT_NAME "loader-glew")
set_target_properties(rt-loader-glad PROPERTIES EXPORT_NAME "loader-glad")
set_target_properties(rt-loader-gl3w PROPERTIES EXPORT_NAME "loader-gl3w")
set_target_properties(rt-loader-glbinding PROPERTIES EXPORT_NAME "loader-glbinding")
set_target_properties(rt-loader-epoxy PROPERTIES EXPORT_NAME "loader-epoxy")

target_compile_definitions(rt-loader-glew PUBLIC RT_LOADER_GLEW)
target_compile_definitions(rt-loader-glad PUBLIC RT_LOADER_GLAD)
target_compile_definitions(rt-loader-gl3w PUBLIC RT_LOADER_GL3W)
target_compile_definitions(rt-loader-glbinding PUBLIC RT_LOADER_GLBINDING)
target_compile_definitions(rt-loader-epoxy PUBLIC RT_LOADER_EPOXY)

# Add the include directory
target_include_directories(rt-loader INTERFACE 
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_include_directories(rt-loader-epoxy PUBLIC
	"$<BUILD_INTERFACE:${EPOXY_INCLUDE}>"
)

target_link_libraries(rt-loader-glew PUBLIC rt-loader GLEW::GLEW)
target_link_libraries(rt-loader-glad PUBLIC rt-loader glad::glad)
target_link_libraries(rt-loader-gl3w PUBLIC rt-loader unofficial::gl3w::gl3w)
target_link_libraries(rt-loader-glbinding PUBLIC rt-loader glbinding::glbinding)
target_link_libraries(rt-loader-epoxy PRIVATE rt-loader "$<BUILD_INTERFACE:${EPOXY_LIB}>")


# Build the tests once the option is enabled.
if(${BUILD_TESTS})
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
	# Set the proper installation path
	set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/rt-loader)
endif()

install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	TYPE INCLUDE
	FILES_MATCHING
	PATTERN "*.h" PATTERN "*.hpp"
)

install(TARGETS rt-loader
	EXPORT loader-targets
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/$<CONFIG>"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
)
install(TARGETS rt-loader-glew
	EXPORT loader-glew-targets
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/$<CONFIG>"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
)
install(TARGETS rt-loader-glad
	EXPORT loader-glad-targets
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/$<CONFIG>"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
)
install(TARGETS rt-loader-gl3w
	EXPORT loader-gl3w-targets
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/$<CONFIG>"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
)
install(TARGETS rt-loader-glbinding
	EXPORT loader-glbinding-targets
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/$<CONFIG>"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
)
install(TARGETS rt-loader-epoxy
	EXPORT loader-epoxy-targets
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/$<CONFIG>"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
)


install_package(
	NAME "rt-loader"
	NAMESPACE "rt::"
	EXPORT "loader-targets"

	COMPONENTS "glew" "gl3w" "glad" "glbinding" "epoxy"

	glew_EXPORT "loader-glew-targets"
	gl3w_EXPORT "loader-gl3w-targets"
	glad_EXPORT "loader-glad-targets"
	glbinding_EXPORT "loader-glbinding-targets"
	epoxy_EXPORT "loader-epoxy-targets"

	VERSION "${CMAKE_PROJECT_VERSION}"

	# Version compatiblity
	COMPATIBILITY "SameMajorVersion"

	# Relative install location of the package config files.
	DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/rt-loader"

	# Pre and Post configuration files for the packages. Files are run as scripts when the package is found.
	PRECONFIG "${CMAKE_CURRENT_SOURCE_DIR}/preconfig.cmake"
	POSTCONFIG "${CMAKE_CURRENT_SOURCE_DIR}/postconfig.cmake"
)