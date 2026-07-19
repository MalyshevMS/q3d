#pragma once

#include <q3d/core/object.hpp>

namespace q3d::object {

class Plane : public core::Object {
public:
    Plane(ptr<gl::Shader> shader, ptr<gl::Texture> texture = nullptr, phys::Transform transform = {});
};

} // namespace q3d::object
