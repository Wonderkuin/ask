#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace engine {

class Window {
public:
    Window() = default;
    ~Window();

    bool create(const char* title, int width, int height);
    void poll_events();
    void swap_buffers();
    bool should_close() const;
    void* native_handle() const { return handle_; }
    int width() const { return width_; }
    int height() const { return height_; }

private:
    GLFWwindow* handle_ = nullptr;
    int width_ = 0;
    int height_ = 0;
};

} // namespace engine
