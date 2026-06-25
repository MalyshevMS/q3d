#pragma once

#include <q3d/core/object.hpp>
#include <q3d/res/resources.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace q3d::object {

class Model : public core::Object {
public:
    Model(ptr<gl::Shader> shader, const Resources::ObjData& objData, phys::Transform transform = {}, ptr<gl::Texture> texture = nullptr);
};

} // namespace q3d::object
