#include <q3d/gl/shader.hpp>
#include <q3d/log/log.hpp>
#include <glad/glad.h>

bool q3d::gl::Shader::compileShader(std::string_view src, const unsigned int type, unsigned int &id) {
    id = glCreateShader(type);

    const char* code = src.cbegin();

    glShaderSource(id, 1, &code, nullptr);
    glCompileShader(id);

    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if (!status) {
        GLchar infolog[1024];
        glGetShaderInfoLog(id, 1024, nullptr, infolog);

        log::error("gl::Shader::compileShader failed:\n{}", infolog);
        return false;
    }

    return true;
}

void q3d::gl::Shader::init() {
    id = glCreateProgram();
}

q3d::gl::Shader::Shader(std::string_view vert_src, std::string_view frag_src) {
    GLuint vs_id = attach(vert_src, GL_VERTEX_SHADER);
    GLuint fs_id = attach(frag_src, GL_FRAGMENT_SHADER);
    init();
    link();
    glDeleteShader(vs_id);
    glDeleteShader(fs_id);
}

unsigned int q3d::gl::Shader::attach(std::string_view src, const unsigned int type) {
    GLuint shader_id;
    if (!compileShader(src, type, shader_id)) {
        glDeleteShader(shader_id);
    }

    glAttachShader(id, shader_id);

    if (type == GL_VERTEX_SHADER) {
        attachedVS = true;
    } else if (type == GL_FRAGMENT_SHADER) {
        attachedFS = true;
    }

    return shader_id;
}

void q3d::gl::Shader::link() {
    if (!(attachedVS && attachedFS)) {
        log::error("gl::Shader::link failed: not all shaders are attached");
        return;
    }

    glLinkProgram(id);

    GLint status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);

    if (!status) {
        GLchar infolog[1024];
        glGetShaderInfoLog(id, 1024, nullptr, infolog);

        log::error("gl::Shader::link failed:\n{}", infolog);
    } else _isLinked = true;
}

void q3d::gl::Shader::use() {
    glUseProgram(id);
}

void q3d::gl::Shader::unuse() {
    glUseProgram(0u);
}
q3d::gl::Shader::~Shader() {
    glDeleteProgram(id);
}