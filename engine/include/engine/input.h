#pragma once
#include <glm/glm.hpp>

struct GLFWwindow;

namespace engine {

class Input {
public:
    void init(GLFWwindow* window);

    bool key_down(int key) const;
    bool key_pressed(int key) const;
    glm::vec2 mouse_position() const;

    void update();

private:
    GLFWwindow* window_ = nullptr;
    bool prev_keys_[512]{};
};

} // namespace engine
