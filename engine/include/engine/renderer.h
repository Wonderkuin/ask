#pragma once
#include <engine/shader.h>
#include <engine/sprite.h>
#include <engine/texture.h>

namespace engine {

class Renderer {
public:
    Renderer() = default;
    ~Renderer();

    bool init(int width, int height);
    void begin_frame();
    void end_frame();
    void draw_sprite(const Sprite& sprite, const Texture& texture);

private:
    Shader shader_;
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
};

} // namespace engine
