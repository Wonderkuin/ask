#include <engine/application.h>
#include <engine/texture.h>
#include <engine/sprite.h>
#include <engine/input.h>
#include <engine/window.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdio>

class DemoGame : public engine::Application {
public:
    void init() override {
        if (!texture_.load_from_file("assets/textures/player.png")) {
            std::fprintf(stderr, "Demo: using 1x1 white texture (colored quad)\n");
        }

        sprite_.position = {512.0f, 384.0f};
        sprite_.scale    = {100.0f, 100.0f};
        sprite_.tint     = {0.3f, 0.7f, 1.0f, 1.0f};
        sprite_.region   = texture_.region(0, 0, texture_.width(), texture_.height());
    }

    void update(float dt) override {
        float speed = 200.0f;
        if (input().key_down(GLFW_KEY_W) || input().key_down(GLFW_KEY_UP))
            sprite_.position.y += speed * dt;
        if (input().key_down(GLFW_KEY_S) || input().key_down(GLFW_KEY_DOWN))
            sprite_.position.y -= speed * dt;
        if (input().key_down(GLFW_KEY_A) || input().key_down(GLFW_KEY_LEFT))
            sprite_.position.x -= speed * dt;
        if (input().key_down(GLFW_KEY_D) || input().key_down(GLFW_KEY_RIGHT))
            sprite_.position.x += speed * dt;

        // Rotate toward mouse
        auto mouse = input().mouse_position();
        auto delta = mouse - sprite_.position;
        sprite_.rotation = std::atan2(delta.y, delta.x);

        // Close on ESC
        if (input().key_pressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(
                static_cast<GLFWwindow*>(window().native_handle()), GLFW_TRUE);
        }
    }

    void render() override {
        renderer().draw_sprite(sprite_, texture_);
    }

protected:
    const char* window_title() const override { return "MiniGL2D Demo"; }

private:
    engine::Texture texture_;
    engine::Sprite  sprite_;
};

int main() {
    DemoGame game;
    game.run();
    return 0;
}
