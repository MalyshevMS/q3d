#pragma once

#include <q3d/obj/light/light.hpp>
#include <q3d/gl/ssbo.hpp>

namespace q3d::core {

class LightManager {
private:
    std::vector<object::Light> lights;

    gl::Ssbo dirLightBuffer = gl::Ssbo(0);
    gl::Ssbo pointLightBuffer = gl::Ssbo(1);
public:
    void addLight(object::Light light);
    void updateBuffers(gl::Shader& shader);
};

}
