#include <q3d/core/active_camera.hpp>
#include <stdexcept>

using namespace q3d;
using namespace core;

ActiveCamera& ActiveCamera::getInstance() {
    static ActiveCamera instance;
    return instance;
}

void ActiveCamera::set(ptr<Camera> cam) {
    getInstance().camera = cam;
}

Camera& ActiveCamera::get() {
    auto& instance = getInstance();
    if (!instance.camera) {
        throw std::runtime_error("ActiveCamera not initialized");
    }
    return *instance.camera;
}

ptr<Camera> ActiveCamera::getPtr() {
    auto& instance = getInstance();
    if (!instance.camera) {
        throw std::runtime_error("ActiveCamera not initialized");
    }
    return instance.camera;
}
