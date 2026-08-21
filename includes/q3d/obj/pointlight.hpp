#pragma once

#include <q3d/obj/light.hpp>

namespace q3d::object {

class PointLight {
private:
    uptr<LightObj> obj;
    ptr<gl::Shader> shader;
public:
    LightProperties properties;
    phys::Transform& transform = obj->transform;
    float linear = 0.09f;
    float quadratic = 0.032f;

    PointLight(ptr<gl::Shader> shader, phys::Transform transform = {}) : obj(std::make_unique<LightObj>(shader, transform)), shader(shader) {}

    void draw() const {
        if (obj) {
            if (shader) {
                shader->use();
                shader->uniform("u_color", properties.color.vec3());
            }

            obj->draw();
        }
    };

    PointLightInternal getInternal() const;
};

}

