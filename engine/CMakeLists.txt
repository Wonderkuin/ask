add_library(engine STATIC
    src/application.cpp
    src/window.cpp
    src/input.cpp
    src/renderer.cpp
    src/shader.cpp
    src/texture.cpp
    src/sprite.cpp
    src/stb_image_impl.cpp
)

target_include_directories(engine PUBLIC include)

target_link_libraries(engine PUBLIC
    glfw
    glad_gl_core_33
    glm::glm
    stb_image
)

# Copy shaders to build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets/shaders
     DESTINATION ${CMAKE_BINARY_DIR})
