#pragma once

#include <q3d/core/object.hpp>

namespace q3d {
    namespace object {
        class Box : public core::Object {
        public:
            Box(ptr<gl::Shader> shader, phys::Transform transform, ptr<gl::Texture> texture);
        };
    }
}