#include <q3d/ui/canvas.hpp>
#include <glad/glad.h>
#include <q3d/core/active_camera.hpp>
#include <q3d/core/object.hpp>
#include <memory>
#include <map>

using namespace q3d;
using namespace ui;

Canvas::Canvas(glm::vec2 size) : size(size) {
    uiCamera = std::make_shared<core::Camera>(size.x / size.y, size.y / 2.f, core::Camera::Type::Orthographic);
    uiCamera->setPosition({ size.x / 2.f, -size.y / 2.f, 1.f });
    uiCamera->setNear(-100.f);
    uiCamera->setFar(100.f);
}

void Canvas::updateSize(glm::vec2 size) {
    this->size = size;
    uiCamera->setAspect(size.x / size.y);
    uiCamera->setFov(size.y / 2);
    uiCamera->setPosition({ size.x / 2.f, -size.y / 2.f, 1.f });
}

void Canvas::add(std::string_view name, ptr<core::Object> obj) {
    obj->features[gl::feature::depthTest] = false;
    core::Scene::add(name, obj);
}

void Canvas::render() const {
    auto oldCamera = core::ActiveCamera::getPtr();
    core::ActiveCamera::set(uiCamera);

    std::multimap<float, ptr<core::Object>> sorted;

    for (const auto& [_, obj] : objects) sorted.insert({obj->transform.position.z, obj});

    for (const auto& [z, obj] : sorted) {
        obj->draw();
    }

    core::ActiveCamera::set(oldCamera);
}
