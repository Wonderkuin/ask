#pragma once
#include <engine/window.h>
#include <engine/input.h>
#include <engine/renderer.h>

namespace engine {

class Application {
public:
    Application() = default;
    virtual ~Application() = default;

    void run();

    Window& window() { return window_; }
    Input& input() { return input_; }
    Renderer& renderer() { return renderer_; }

protected:
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

    virtual const char* window_title() const { return "minigl2d"; }
    virtual int window_width() const { return 1024; }
    virtual int window_height() const { return 768; }

private:
    Window window_;
    Input input_;
    Renderer renderer_;
};

} // namespace engine
