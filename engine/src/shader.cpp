#include <engine/shader.h>
#include <cstdio>
#include <fstream>
#include <sstream>

namespace engine {

Shader::~Shader() {
    if (program_) glDeleteProgram(program_);
}

static GLuint compile(GLenum type, const char* source) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &source, nullptr);
    glCompileShader(s);

    GLint ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(s, sizeof(log), nullptr, log);
        std::fprintf(stderr, "Shader compile error: %s\n", log);
        glDeleteShader(s);
        return 0;
    }
    return s;
}

static std::string read_file(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) {
        std::fprintf(stderr, "Cannot open file: %s\n", path.c_str());
        return {};
    }
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

bool Shader::load(const std::string& vert_path, const std::string& frag_path) {
    auto vert_src = read_file(vert_path);
    auto frag_src = read_file(frag_path);
    if (vert_src.empty() || frag_src.empty()) return false;

    GLuint vs = compile(GL_VERTEX_SHADER, vert_src.c_str());
    GLuint fs = compile(GL_FRAGMENT_SHADER, frag_src.c_str());
    if (!vs || !fs) return false;

    program_ = glCreateProgram();
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);
    glLinkProgram(program_);

    GLint ok;
    glGetProgramiv(program_, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetProgramInfoLog(program_, sizeof(log), nullptr, log);
        std::fprintf(stderr, "Shader link error: %s\n", log);
        glDeleteProgram(program_);
        program_ = 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program_ != 0;
}

void Shader::use() const { glUseProgram(program_); }

void Shader::set_int(const char* name, int value) const {
    glUniform1i(glGetUniformLocation(program_, name), value);
}

void Shader::set_mat4(const char* name, const float* value) const {
    glUniformMatrix4fv(glGetUniformLocation(program_, name), 1, GL_FALSE, value);
}

void Shader::set_vec4(const char* name, const float* value) const {
    glUniform4fv(glGetUniformLocation(program_, name), 1, value);
}

} // namespace engine
