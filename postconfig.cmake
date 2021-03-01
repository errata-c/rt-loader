
string(TOLOWER "${rt-loader_FIND_COMPONENTS}" "COMPS")

if("epoxy" IN_LIST "COMPS")
	find_path(EPOXY_INCLUDE "epoxy/gl.h")
	if("${EPOXY_INCLUDE}" STREQUAL "EPOXY_INCLUDE-NOTFOUND")
		if("${rt-loader_FIND_REQUIRED_epoxy}")
			set(rt-loader_FOUND FALSE)
		endif()
	else()
		set_target_properties(rt::loader-epoxy PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "$<BUILD_INTERFACE:${EPOXY_INCLUDE}>")
	endif()
endif()