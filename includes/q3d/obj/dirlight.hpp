#pragma once

#include <q3d/obj/light.hpp>

namespace q3d::object {

class DirLight {
private:
    uptr<LightObj> obj;
    ptr<gl::Shader> shader;
public:
    LightProperties properties;
    phys::Transform& transform = obj->transform;

    DirLight(ptr<gl::Shader> shader, phys::Transform transform = {}) : obj(std::make_unique<LightObj>(shader, transform)), shader(shader), properties() {}

    void draw() const {
        if (obj) {
            if (shader) {
                shader->use();
                shader->uniform("u_color", properties.color.vec3());
            }

            obj->draw();
        }
    }

    DirLightInternal getInternal() const;
};

}
