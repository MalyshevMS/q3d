#include <q3d/core/scene.hpp>
#include <q3d/core/object.hpp>
#include <q3d/core/active_camera.hpp>
#include <glm/common.hpp>
#include <map>

using namespace q3d;
using namespace q3d::core;

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

void q3d::core::Scene::render() {
    using Order = std::map<float, ptr<Object>>;
    Order sorted;
    for (const auto& [_, obj] : objects) {
        float distance = glm::length(
            ActiveCamera::getInstance()->cam().getPosition() - obj->transform.position
        );
        sorted[distance] = obj;
    }

    for(Order::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++) {
        it->second->draw();
    }
}