#include <q3d/core/camera.hpp>
#include <q3d/core/active_camera.hpp>
#include <q3d/core/object.hpp>
#include <q3d/ui/canvas.hpp>
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

void Canvas::render() const {
    auto oldCamera = core::ActiveCamera::getPtr();
    core::ActiveCamera::set(uiCamera);

    std::multimap<float, ptr<core::Object>> sorted;

    for (const auto& [_, obj] : objects) {
        auto& targetZ = obj->transform.position.z;

        while (sorted.find(targetZ) != sorted.end()) {
            targetZ += 0.000001f;
        }

        sorted.insert({targetZ, obj});
    }

    for (const auto& [z, obj] : sorted) {
        obj->draw();
    }

    core::ActiveCamera::set(oldCamera);
}
