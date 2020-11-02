add_executable(Laucher
main.cpp
spp_tests.cpp
blocks.cpp
spp_genetic.cpp
spp_gfx_rep.cpp
spp_individual.cpp
glad.c
)

set_target_properties(Laucher PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../bin/")

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
    target_include_directories(Laucher PUBLIC ${OPENGL_INCLUDE_DIR})
    target_link_libraries(Laucher ${OPENGL_gl_LIBRARY})
endif()

target_link_libraries(Laucher glfw)
