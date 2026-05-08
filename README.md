# MiniGL2D Engine

A lightweight 2D game engine built on OpenGL 3.3 Core, GLFW, and GLM.

## Project Structure

```
ask/
├── CMakeLists.txt            # Root build config, fetches all dependencies
├── assets/
│   ├── shaders/
│   │   ├── sprite.vert       # Sprite vertex shader
│   │   └── sprite.frag       # Sprite fragment shader
│   └── textures/
│       └── player.png        # Example texture
├── engine/                   # Static library: the engine core
│   ├── CMakeLists.txt
│   ├── include/engine/
│   │   ├── application.h
│   │   ├── window.h
│   │   ├── input.h
│   │   ├── renderer.h
│   │   ├── shader.h
│   │   ├── texture.h
│   │   └── sprite.h
│   └── src/
│       ├── application.cpp
│       ├── window.cpp
│       ├── input.cpp
│       ├── renderer.cpp
│       ├── shader.cpp
│       ├── texture.cpp
│       ├── sprite.cpp
│       └── stb_image_impl.cpp
└── example/                  # Demo game
    ├── CMakeLists.txt
    └── main.cpp
```

## Dependencies

All dependencies are fetched automatically by CMake FetchContent:

| Library | Version | Purpose |
|---------|---------|---------|
| GLFW | 3.3.9 | Window creation and input |
| GLAD | v2.0.8 | OpenGL 3.3 Core function loader |
| GLM | 1.0.1 | Math (vectors, matrices, transforms) |
| stb_image | master | Image loading (PNG, JPG, etc.) |

## Engine Components

### Application

The base class for your game. Override three lifecycle methods:

- `init()` — called once at startup
- `update(float dt)` — called each frame with delta time
- `render()` — called each frame for drawing

Access subsystems through getters: `window()`, `input()`, `renderer()`.

Override `window_title()`, `window_width()`, `window_height()` to configure the window.

### Window

Wraps GLFW. Creates an OpenGL 3.3 Core context and manages the window lifecycle. Provides:

- `poll_events()` / `swap_buffers()` — event loop
- `should_close()` — exit check
- `native_handle()` — raw `GLFWwindow*` for advanced usage

### Input

Keyboard and mouse state tracking:

- `key_down(key)` — is key currently held?
- `key_pressed(key)` — was key just pressed this frame?
- `mouse_position()` — cursor position as `glm::vec2`

`update()` must be called each frame to track key state transitions (handled automatically by `Application`).

### Renderer

Draws sprites with an orthographic projection (default 1024x768, Y-down):

- `init(width, height)` — compile shaders, create quad VAO
- `begin_frame()` — clear screen
- `draw_sprite(sprite, texture)` — draw a sprite
- `end_frame()` — placeholder for post-processing

### Shader

Compiles and links GLSL vertex/fragment shader pairs:

- `load(vert_path, frag_path)` — compile and link from files
- `use()` — bind the program
- `set_int()`, `set_mat4()`, `set_vec4()` — set uniforms

### Texture

Loads images via stb_image and creates OpenGL textures:

- `load_from_file(path)` — load PNG/JPG/etc.
- `bind(unit)` — bind to a texture slot
- `region(x, y, w, h)` — get UV coordinates for a sub-rectangle (useful for sprite sheets)

### Sprite

A simple data struct describing a 2D sprite:

| Field | Type | Default | Description |
|-------|------|---------|-------------|
| `position` | `glm::vec2` | (0, 0) | Center position in pixels |
| `scale` | `glm::vec2` | (1, 1) | Size in pixels |
| `rotation` | `float` | 0 | Angle in radians |
| `tint` | `glm::vec4` | (1,1,1,1) | Color multiplier (RGBA) |
| `region` | `Texture::Region` | full texture | UV sub-rectangle |

## Shaders

### sprite.vert

Transforms quad vertices by `model` and `projection` matrices. Maps vertex UVs through `uv_rect` to support sprite sheet sub-regions.

### sprite.frag

Samples the texture and multiplies by the `tint` uniform for coloring/alpha.

## Building

```bash
cd build
cmake ..
cmake --build . -j$(nproc)
```

## Running

```bash
cd build
./example/example_game
```

The executable looks for `shaders/` and `assets/` relative to the working directory, so always run from the `build/` directory.

### Controls

- **WASD / Arrow keys** — move sprite
- **Mouse** — sprite rotates toward cursor
- **ESC** — quit

## Writing a New Game

Subclass `engine::Application` and implement the three lifecycle methods:

```cpp
#include <engine/application.h>

class MyGame : public engine::Application {
    void init() override {
        // Load textures, set up sprites
    }

    void update(float dt) override {
        // Handle input, move objects
    }

    void render() override {
        renderer().draw_sprite(sprite_, texture_);
    }
};

int main() {
    MyGame game;
    game.run();
    return 0;
}
```
