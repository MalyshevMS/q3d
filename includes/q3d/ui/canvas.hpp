#pragma once

#include <q3d/core/scene.hpp>
#include <q3d/core/camera.hpp>

namespace q3d {
    namespace ui {
        class Canvas : public core::Scene {
        private:
            ptr<core::Camera> uiCamera;
            glm::vec2 size;
        public:
            Canvas(glm::vec2 size);
            void updateSize(glm::vec2 size);
            void render() const override;
        };
    }
}
