#pragma once

#include <q3d/core/camera.hpp>
#include <q3d/res/ptr.hpp>

namespace q3d {
    namespace core {
        class ActiveCamera {
        private:
            ActiveCamera(uptr<Camera> camera);
            uptr<Camera> camera;

            static ActiveCamera* instance;
        public:
            ActiveCamera* getInstance(uptr<Camera> camera = nullptr);
            Camera& cam() { return *camera; }
        };
    }
}