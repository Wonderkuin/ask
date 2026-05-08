#pragma once
#include <glm/glm.hpp>
#include <engine/texture.h>

namespace engine {

struct Sprite {
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 scale    = {1.0f, 1.0f};
    float rotation     = 0.0f;
    glm::vec4 tint     = {1.0f, 1.0f, 1.0f, 1.0f};
    Texture::Region region = {0.0f, 0.0f, 1.0f, 1.0f};
};

} // namespace engine
