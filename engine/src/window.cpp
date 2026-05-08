#include <engine/window.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstdio>

namespace engine {

static void framebuffer_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::~Window() {
    if (handle_) {
        glfwDestroyWindow(handle_);
        glfwTerminate();
    }
}

bool Window::create(const char* title, int width, int height) {
    if (!glfwInit()) {
        std::fprintf(stderr, "GLFW init failed\n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!handle_) {
        std::fprintf(stderr, "Window creation failed\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(handle_);
    glfwSetFramebufferSizeCallback(handle_, framebuffer_callback);

    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
        std::fprintf(stderr, "GLAD init failed\n");
        return false;
    }

    width_ = width;
    height_ = height;
    return true;
}

void Window::poll_events() { glfwPollEvents(); }
void Window::swap_buffers() { glfwSwapBuffers(handle_); }
bool Window::should_close() const { return glfwWindowShouldClose(handle_); }

} // namespace engine
