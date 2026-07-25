#pragma once

#include <q3d/core/material.hpp>
#include <q3d/res/ptr.hpp>
#include <q3d/phys/transform.hpp>
#include <q3d/gl/shader.hpp>
#include <q3d/gl/texture.hpp>
#include <q3d/gl/vao.hpp>
#include <q3d/gl/gl.hpp>

namespace q3d::core {

class Object {
protected:
    ptr<gl::Shader> shader;
    ptr<gl::Texture> texture = nullptr; // Remember to always check if texture is not `nullptr`!

    uptr<gl::Vbo> vbo; // Don't forget to init those!
    uptr<gl::Ibo> ibo;
    uptr<gl::Vao> vao;

public:
    std::unordered_map<gl::feature, bool> features = {
        { gl::feature::depthTest, true },
        { gl::feature::blend, true },
    };

    phys::Transform transform;
    ptr<core::Material> material;
    bool doDraw = true;

    Object(ptr<gl::Shader> shader, ptr<gl::Texture> texture = nullptr, phys::Transform transform = {})
            : shader(shader), transform(transform), texture(texture) {}

    virtual void draw() const;
    virtual void drawGeometryOnly() const;

    ptr<gl::Shader> getShader() const { return shader; }
};

} // namespace q3d::core
