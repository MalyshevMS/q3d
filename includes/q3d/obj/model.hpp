#pragma once

#include <q3d/core/object.hpp>
#include <q3d/res/resources.hpp>
#include <q3d/res/vertex.hpp>

namespace q3d::object {

class Model : public core::Object {
public:
    Model(ptr<gl::Shader> shader, const ObjData& objData, ptr<gl::Texture> texture = nullptr, phys::Transform transform = {});
};

} // namespace q3d::object
