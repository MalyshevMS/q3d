#pragma once

#include <q3d/obj/light.hpp>

namespace q3d::object {

class PointLight {
private:
    uptr<LightObj> obj;
public:
    LightProperties properties;
    float linear = 0.09f;
    float quadratic = 0.032f;

    PointLight(ptr<gl::Shader> shader, phys::Transform transform) : obj(std::make_unique<LightObj>(shader, transform)) {}

    void draw() const {
        if (obj) obj->draw();
    };

    PointLightInternal getInternal() const;
};

}

