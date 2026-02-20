#pragma once

#include <q3d/res/ptr.hpp>
#include <q3d/phys/transform.hpp>
#include <q3d/gl/shader.hpp>
#include <q3d/gl/texture.hpp>
#include <q3d/gl/vao.hpp>

namespace q3d {
    namespace core {
        class Object {
        protected:
            ptr<gl::Shader> shader;
            ptr<gl::Texture> texture = nullptr; // Remember to always check if texture is not `nullptr`!

            uptr<gl::Vbo> vbo; // Don't forget to init those!
            uptr<gl::Ibo> ibo;
            uptr<gl::Vao> vao;
        public:
            phys::Transform transform;
            bool doDraw = true;

            Object(ptr<gl::Shader> shader, phys::Transform transform, ptr<gl::Texture> texture = nullptr)
                   : shader(shader), transform(transform), texture(texture) {}

            virtual void draw() const;
        };
    }
} 
