#pragma once

#include <q3d/core/object.hpp>

namespace q3d::object {

class Box : public core::Object {
public:
    Box(ptr<gl::Shader> shader, ptr<gl::Texture> texture, phys::Transform transform);
};

} // namespace q3d::object
