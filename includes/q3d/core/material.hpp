#pragma once

#include <glm/vec3.hpp>
#include <q3d/gl/shader.hpp>

namespace q3d::core {

struct Material {
    glm::vec3 ambient  = glm::vec3(0.1f);
    glm::vec3 diffuse  = glm::vec3(1.f);
    glm::vec3 specular = glm::vec3(1.f);
    float shininess = 32.f;

    void use(q3d::gl::Shader& shader) const {
        shader.uniform("u_material.ambient", ambient);
        shader.uniform("u_material.diffuse", diffuse);
        shader.uniform("u_material.specular", specular);
        shader.uniform("u_material.shininess", shininess);
    }
};

} // namespace q3d::core
