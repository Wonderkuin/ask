#pragma once
#include <glad/gl.h>
#include <string>

namespace engine {

class Shader {
public:
    Shader() = default;
    ~Shader();

    bool load(const std::string& vert_path, const std::string& frag_path);
    void use() const;
    void set_int(const char* name, int value) const;
    void set_mat4(const char* name, const float* value) const;
    void set_vec4(const char* name, const float* value) const;
    GLuint id() const { return program_; }

private:
    GLuint program_ = 0;
};

} // namespace engine
