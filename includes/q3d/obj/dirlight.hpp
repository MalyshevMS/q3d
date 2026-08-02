#pragma once

#include <q3d/obj/light.hpp>

namespace q3d::object {

class DirLight {
private:
    uptr<LightObj> obj;
public:
    LightProperties properties;

    DirLight(ptr<gl::Shader> shader, phys::Transform transform = {}) : obj(std::make_unique<LightObj>(shader, transform)) {}

    void draw() const {
        if (obj) obj->draw();
    }

    DirLightInternal getInternal() const;
};

}
