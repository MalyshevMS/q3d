#include <q3d/core/scene.hpp>
#include <q3d/core/object.hpp>
#include <q3d/core/active_camera.hpp>
#include <map>

using namespace q3d;
using namespace core;
using namespace object;

void Scene::add(std::string_view name, ptr<Object> obj) {
    objects[name.data()] = obj;
}

void Scene::remove(std::string_view name) {
    objects.erase(name.data());
}

ptr<Object> Scene::get(std::string_view name) {
    auto it = objects.find(name.data());

    if (it != objects.end()) return it->second;
    return nullptr;
}

void Scene::addDirLight(std::string_view name, const DirLight& light) {
    dirLights[name.data()] = std::make_shared<DirLight>(light);
}

void Scene::addPointLight(std::string_view name, const PointLight& light) {
    pointLights[name.data()] = std::make_shared<PointLight>(light);
}

void Scene::addSpotLight(std::string_view name, const SpotLight& light) {
    spotLights[name.data()] = std::make_shared<SpotLight>(light);
}

ptr<DirLight> Scene::getDirLight(std::string_view name) {
    auto it = dirLights.find(name.data());

    if (it != dirLights.end()) return it->second;
    return nullptr;
}

ptr<PointLight> Scene::getPointLight(std::string_view name) {
    auto it = pointLights.find(name.data());

    if (it != pointLights.end()) return it->second;
    return nullptr;
}

ptr<SpotLight> Scene::getSpotLight(std::string_view name) {
    auto it = spotLights.find(name.data());

    if (it != spotLights.end()) return it->second;
    return nullptr;
}

void q3d::core::Scene::render() {
    if (!dirLights.empty()) {
        std::vector<DirLight> raw;
        raw.reserve(dirLights.size());

        for (const auto& [_, l] : dirLights) {
            raw.push_back(*l);
        }

        dirLightSsbo.updateData(std::span(raw));
    }

    if (!pointLights.empty()) {
        std::vector<PointLight> raw;
        raw.reserve(pointLights.size());

        for (const auto& [_, l] : pointLights) {
            raw.push_back(*l);
        }

        pointLightSsbo.updateData(std::span(raw));
    }

    if (!spotLights.empty()) {
        std::vector<SpotLight> raw;
        raw.reserve(spotLights.size());

        for (const auto& [_, l] : spotLights) {
            raw.push_back(*l);
        }

        spotLightSsbo.updateData(std::span(raw));
    }


    using Order = std::map<float, ptr<Object>>;
    Order sorted;
    for (const auto& [_, obj] : objects) {
        float distance = glm::length(
            ActiveCamera::get().getPosition() - obj->transform.position
        );
        sorted[distance] = obj;
    }

    for(Order::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++) {
        it->second->draw();
    }
}
