#pragma once

#include <glm/vec3.hpp>
#include <variant>

namespace q3d::gl {
    class Shader;
}

namespace q3d::object {

struct alignas(16) DirLight {
    glm::vec3 direction = glm::vec3(-1.f);
    float pad1 = 0.f; // those are padding variable they doesn't serve any function

    glm::vec3 ambient = glm::vec3(0.1f);
    float pad2 = 0.f;

    glm::vec3 diffuse = glm::vec3(0.8f);
    float pad3 = 0.f;

    glm::vec3 specular = glm::vec3(1.f);
    float pad4 = 0.f;
};

struct alignas(16) PointLight {
    glm::vec3 position = glm::vec3(0.f);
    float constant = 1.f;

    glm::vec3 ambient = glm::vec3(0.1f);
    float linear = 0.09f;

    glm::vec3 diffuse = glm::vec3(0.8f);
    float quadratic = 0.032f;

    glm::vec3 specular = glm::vec3(1.f);
    float pad = 0.f;
};

struct alignas(16) SpotLight {
    glm::vec3 position = glm::vec3(0.f);
    float cutOff = 0.91f;

    glm::vec3 direction = glm::vec3(0.f, -1.f, 0.f);
    float outerCutOff = 0.82f;

    glm::vec3 ambient = glm::vec3(0.1f);
    float constant = 1.f;

    glm::vec3 diffuse = glm::vec3(1.f);
    float linear = 0.09f;

    glm::vec3 specular = glm::vec3(1.f);
    float quadratic = 0.032f;
};

using Light = std::variant<DirLight, PointLight, SpotLight>;

} // namespace q3d::object
