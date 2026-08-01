#include <q3d/obj/spotlight.hpp>
#include <glm/trigonometric.hpp>

using namespace q3d;
using namespace object;

SpotLightInternal SpotLight::getInternal() const {
    float outer = glm::radians(angle * 0.5f);
    float inner = outer * (1.f - glm::clamp(blend, 0.f, 1.f));

    auto model = obj->transform.getModelMatrix();
    auto direction = glm::normalize(-glm::vec3(model[2]));

    return {
        .position = obj->transform.position,
        .cutOff = inner,
        .direction = direction,
        .outerCutOff = outer,
        .ambient = properties.ambient * properties.color.vec3(),
        .constant = 1.f,
        .diffuse = properties.diffuse * properties.color.vec3(),
        .linear = linear,
        .specular = properties.specular * properties.color.vec3(),
        .quadratic = quadratic,
    };
}
