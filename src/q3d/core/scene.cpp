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

void Scene::addLight(std::string_view name, ptr<Light> light) {
    lights[name.data()] = light;
}

void Scene::removeLight(std::string_view name) {
    lights.erase(name.data());
}

ptr<Light> Scene::getLight(std::string_view name) {
    auto it = lights.find(name.data());

    if (it != lights.end()) return it->second;
    return nullptr;
}

void q3d::core::Scene::render() const {
    using Order = std::map<float, ptr<Object>>;
    Order sorted;
    for (const auto& [_, obj] : objects) {
        float distance = glm::length(
            ActiveCamera::get().getPosition() - obj->transform.position
        );
        sorted[distance] = obj;
    }

    LightManager lm;
    for (const auto& [_, l] : lights) {
        lm.addLight(*l);
    }

    for(Order::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++) {
        it->second->draw(lm);
    }
}
