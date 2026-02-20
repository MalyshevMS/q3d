#pragma once

#include <q3d/core/camera.hpp>
#include <q3d/res/ptr.hpp>

namespace q3d {
    namespace core {
        class ActiveCamera {
        private:
            ActiveCamera(ptr<Camera> camera);
            ptr<Camera> camera;

            static ActiveCamera* instance;
        public:
            static ActiveCamera* getInstance(ptr<Camera> camera = nullptr);
            Camera& cam() { return *camera; }
        };
    }
}