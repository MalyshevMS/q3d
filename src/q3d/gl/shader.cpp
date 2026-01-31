#include <q3d/gl/shader.hpp>
#include <q3d/log/log.hpp>
#include <glad/glad.h>

using namespace q3d;

unsigned int gl::Shader::typeToGl(Type type) {
    switch(type) {
        case Type::Vertex: return GL_VERTEX_SHADER;
        case Type::Fragment: return GL_FRAGMENT_SHADER;
    }
    return 0;
}

bool gl::Shader::compileShader(std::string_view src, const Type type, unsigned int &id) {
    id = glCreateShader(typeToGl(type));

    const char* code = src.data();

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

void gl::Shader::init() {
    id = glCreateProgram();
}

gl::Shader::Shader(std::string_view vert_src, std::string_view frag_src) {
    GLuint vs_id = attach(vert_src, Type::Vertex);
    GLuint fs_id = attach(frag_src, Type::Fragment);
    init();
    link();
    glDeleteShader(vs_id);
    glDeleteShader(fs_id);
}

unsigned int gl::Shader::attach(std::string_view src, const Type type) {
    GLuint shader_id;
    if (!compileShader(src, type, shader_id)) {
        glDeleteShader(shader_id);
    }

    glAttachShader(id, shader_id);

    if (type == Type::Vertex) {
        attachedVS = true;
    } else if (type == Type::Fragment) {
        attachedFS = true;
    }

    return shader_id;
}

void gl::Shader::link() {
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

void gl::Shader::use() {
    glUseProgram(id);
}

void gl::Shader::unuse() {
    glUseProgram(0u);
}
gl::Shader::~Shader() {
    glDeleteProgram(id);
}