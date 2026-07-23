#include <q3d/core/light_manager.hpp>

using namespace q3d;
using namespace core;
using namespace gl;
using namespace object;

template<class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};

void LightManager::addLight(Light light) {
    lights.push_back(light);
}

void LightManager::updateBuffers(Shader& shader) {
    std::vector<DirLight> dirLights;
    std::vector<PointLight> pointLights;

    for (const auto& l : lights) {
        std::visit(overloaded{
            [&](const DirLight& dir){
                dirLights.push_back(dir);
            },

            [&](const PointLight pt){
                pointLights.push_back(pt);
            }
        }, l);
    }

    dirLightBuffer.updateData(dirLights.data(), dirLights.size());
    pointLightBuffer.updateData(pointLights.data(), pointLights.size());
}
