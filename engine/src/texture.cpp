#include <engine/texture.h>
#include <stb_image.h>
#include <cstdio>

namespace engine {

Texture::~Texture() {
    if (tex_) glDeleteTextures(1, &tex_);
}

bool Texture::load_from_file(const std::string& path) {
    int channels;
    unsigned char* data = stbi_load(path.c_str(), &width_, &height_, &channels, 4);
    if (!data) {
        std::fprintf(stderr, "Failed to load texture: %s\n", path.c_str());
        return false;
    }

    glGenTextures(1, &tex_);
    glBindTexture(GL_TEXTURE_2D, tex_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    stbi_image_free(data);
    return true;
}

void Texture::bind(GLuint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, tex_);
}

Texture::Region Texture::region(int x, int y, int w, int h) const {
    float iw = static_cast<float>(width_);
    float ih = static_cast<float>(height_);
    return {
        x / iw,        y / ih,
        (x + w) / iw,  (y + h) / ih
    };
}

} // namespace engine
