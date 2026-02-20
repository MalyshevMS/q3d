#include <q3d/core/active_camera.hpp>

using namespace q3d::core;

ActiveCamera* ActiveCamera::instance = nullptr;

ActiveCamera::ActiveCamera(ptr<Camera> camera) {
    this->camera = std::move(camera);
}

ActiveCamera* ActiveCamera::getInstance(ptr<Camera> camera) {
    if (instance == nullptr) instance = new ActiveCamera(std::move(camera));
    return instance;
}