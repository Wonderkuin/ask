#include <engine/application.h>
#include <GLFW/glfw3.h>
#include <cstdio>

namespace engine {

void Application::run() {
    if (!window_.create(window_title(), window_width(), window_height())) {
        std::fprintf(stderr, "Failed to create window\n");
        return;
    }

    input_.init(static_cast<GLFWwindow*>(window_.native_handle()));

    if (!renderer_.init(window_width(), window_height())) {
        std::fprintf(stderr, "Failed to init renderer\n");
        return;
    }

    init();

    float last_time = static_cast<float>(glfwGetTime());
    while (!window_.should_close()) {
        float now = static_cast<float>(glfwGetTime());
        float dt = now - last_time;
        last_time = now;

        window_.poll_events();
        input_.update();
        update(dt);

        renderer_.begin_frame();
        render();
        renderer_.end_frame();

        window_.swap_buffers();
    }
}

} // namespace engine
