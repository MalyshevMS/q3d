#pragma once

#include <q3d/obj/light.hpp>

namespace q3d::object {

class SpotLight {
private:
    uptr<LightObj> obj;
public:
    LightProperties properties;
    float linear = 0.09f;
    float quadratic = 0.032f;
    float angle = 45.f;
    float blend = 0.1f;

    SpotLight(ptr<gl::Shader> shader, phys::Transform transform) : obj(std::make_unique<LightObj>(shader, transform)) {}

    void draw() const {
        if (obj) obj->draw();
    };

    SpotLightInternal getInternal() const;
};

}
