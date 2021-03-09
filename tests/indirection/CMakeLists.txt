
add_library(foo STATIC "lib.cpp")
target_include_directories(foo PUBLIC "include")
target_link_libraries(foo PUBLIC rt-loader)

add_executable(indirection_test "main.cpp")
target_link_libraries(indirection_test PRIVATE rt-loader-glew foo)