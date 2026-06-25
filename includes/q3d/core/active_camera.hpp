#pragma once

#include <q3d/core/camera.hpp>
#include <q3d/res/ptr.hpp>

namespace q3d::core {

class ActiveCamera {
private:
    ActiveCamera() = default;
    ~ActiveCamera() = default;
    ActiveCamera(const ActiveCamera&) = delete;
    ActiveCamera& operator=(const ActiveCamera&) = delete;

    ptr<Camera> camera;
    static ActiveCamera& getInstance();
public:
    static void set(ptr<Camera> cam);
    static Camera& get();
    static ptr<Camera> getPtr();
};

} // namespace q3d::core
