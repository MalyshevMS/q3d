#pragma once

#include <q3d/core/object.hpp>

namespace q3d {
    namespace q2d {
        class Plane : public core::Object {
        public:
            Plane(ptr<gl::Shader> shader, phys::Transform transform = {}, ptr<gl::Texture> texture = nullptr);
        };
    }
}