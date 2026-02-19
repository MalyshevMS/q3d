#include <q3d/core/active_camera.hpp>

using namespace q3d;

ActiveCamera* ActiveCamera::instance = nullptr;

ActiveCamera::ActiveCamera(uptr<Camera> camera) {
    this->camera = std::move(camera);
}

ActiveCamera* ActiveCamera::getInstance(uptr<Camera> camera) {
    if (instance == nullptr) return new ActiveCamera(std::move(camera));
    else return instance;
}