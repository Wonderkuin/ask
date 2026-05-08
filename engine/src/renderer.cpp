#include <engine/renderer.h>
#include <engine/shader.h>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine {

Renderer::~Renderer() {
    if (vao_) glDeleteVertexArrays(1, &vao_);
    if (vbo_) glDeleteBuffers(1, &vbo_);
}

bool Renderer::init(int width, int height) {
    if (!shader_.load("shaders/sprite.vert", "shaders/sprite.frag"))
        return false;

    float vertices[] = {
        // pos       // uv
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,
    };

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          reinterpret_cast<void*>(2 * sizeof(float)));

    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Renderer::begin_frame() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::end_frame() {}

void Renderer::draw_sprite(const Sprite& sprite, const Texture& texture) {
    shader_.use();

    glm::mat4 model = glm::translate(glm::mat4(1.0f),
                           glm::vec3(sprite.position, 0.0f)) *
                       glm::rotate(glm::mat4(1.0f), sprite.rotation,
                           glm::vec3(0.0f, 0.0f, 1.0f)) *
                       glm::scale(glm::mat4(1.0f),
                           glm::vec3(sprite.scale, 1.0f));

    glm::mat4 proj = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);

    shader_.set_mat4("model", glm::value_ptr(model));
    shader_.set_mat4("projection", glm::value_ptr(proj));

    float uv[] = { sprite.region.u0, sprite.region.v0,
                   sprite.region.u1, sprite.region.v1 };
    shader_.set_vec4("uv_rect", uv);

    texture.bind(0);
    shader_.set_int("image", 0);
    shader_.set_vec4("tint", &sprite.tint[0]);

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

} // namespace engine
