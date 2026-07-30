#include <q3d/gl/shader.hpp>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

using namespace q3d;
using namespace gl;

int Shader::locate(std::string_view name) {
    return glGetUniformLocation(id, name.data());
}

void Shader::uniform(std::string_view name, bool val) {
    glUniform1i(locate(name), val);
}

void Shader::uniform(std::string_view name, int val) {
    glUniform1i(locate(name), val);
}

void Shader::uniform(std::string_view name, float val) {
    glUniform1f(locate(name), val);
}

void Shader::uniform(std::string_view name, glm::vec2 val) {
    glUniform2fv(locate(name), 1, glm::value_ptr(val));
}

void Shader::uniform(std::string_view name, glm::vec3 val) {
    glUniform3fv(locate(name), 1, glm::value_ptr(val));
}

void Shader::uniform(std::string_view name, glm::mat3 val) {
    glUniformMatrix3fv(locate(name), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::uniform(std::string_view name, glm::mat4 val) {
    glUniformMatrix4fv(locate(name), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::uniform(std::string_view name, std::span<const glm::mat4> values) {
    glUniformMatrix4fv(locate(name), static_cast<GLsizei>(values.size()), GL_FALSE, glm::value_ptr(values[0]));
}
