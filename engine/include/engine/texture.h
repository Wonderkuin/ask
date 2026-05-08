#pragma once
#include <glad/gl.h>
#include <string>

namespace engine {

class Texture {
public:
    Texture() = default;
    ~Texture();

    bool load_from_file(const std::string& path);
    void bind(GLuint unit = 0) const;
    int width() const { return width_; }
    int height() const { return height_; }

    struct Region {
        float u0, v0, u1, v1;
    };
    Region region(int x, int y, int w, int h) const;

private:
    GLuint tex_ = 0;
    int width_ = 0;
    int height_ = 0;
};

} // namespace engine
