#include <q3d/obj/dirlight.hpp>

using namespace q3d;
using namespace object;

DirLightInternal DirLight::getInternal() const {
    auto model = obj->transform.getModelMatrix();
    auto direction = glm::normalize(-glm::vec3(model[2]));

    return {
        .direction = direction,
        .ambient  = properties.ambient  * properties.color.vec3(),
        .diffuse  = properties.diffuse  * properties.color.vec3(),
        .specular = properties.specular * properties.color.vec3(),
    };
}
