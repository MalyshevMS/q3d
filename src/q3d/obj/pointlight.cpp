#include <q3d/obj/pointlight.hpp>

using namespace q3d;
using namespace object;

PointLightInternal PointLight::getInternal() const {
    return {
        .position = obj->transform.position,
        .constant = 1.f,
        .ambient = properties.ambient * properties.color.vec3(),
        .linear = linear,
        .diffuse = properties.diffuse * properties.color.vec3(),
        .quadratic = quadratic,
        .specular = properties.specular * properties.color.vec3(),
    };
}
