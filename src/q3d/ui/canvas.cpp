#include <q3d/core/camera.hpp>
#include <q3d/core/active_camera.hpp>
#include <q3d/core/object.hpp>
#include <q3d/ui/canvas.hpp>
#include <memory>
#include <map>

using namespace q3d::ui;

Canvas::Canvas(glm::vec2 size) : size(size) {
    uiCamera = std::make_shared<core::Camera>(size.x / size.y, size.y / 2.f, core::Camera::Type::Orthographic);
}

void Canvas::render() const {
    auto oldCamera = core::ActiveCamera::getPtr();
    core::ActiveCamera::set(uiCamera);

    using Order = std::map<float, ptr<core::Object>>;
    Order sorted;
    for (const auto& [_, obj] : objects) {
        sorted[obj->transform.position.z] = obj;
    }

    for (Order::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++) {
        it->second->draw();
    }

    core::ActiveCamera::set(oldCamera);
}
