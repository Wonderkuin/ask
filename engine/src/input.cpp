#include <engine/input.h>
#include <GLFW/glfw3.h>

namespace engine {

void Input::init(GLFWwindow* window) { window_ = window; }

bool Input::key_down(int key) const {
    return glfwGetKey(window_, key) == GLFW_PRESS;
}

bool Input::key_pressed(int key) const {
    return key_down(key) && !prev_keys_[key];
}

glm::vec2 Input::mouse_position() const {
    double x, y;
    glfwGetCursorPos(window_, &x, &y);
    return {static_cast<float>(x), static_cast<float>(y)};
}

void Input::update() {
    for (int i = 0; i < 512; ++i)
        prev_keys_[i] = key_down(i);
}

} // namespace engine
