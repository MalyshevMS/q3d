#pragma once

#include <q3d/res/fs.hpp>
#include <q3d/res/ptr.hpp>
#include <q3d/res/vertex.hpp>

// Forward declarations
namespace q3d {

namespace gl {
    class Texture;
    class Shader;
}

namespace ui {
    class Font;
}

namespace core {
    struct Material;
}

}

namespace q3d::loader {
    ptr<gl::Texture> texture(bytes raw);
    ptr<gl::Shader> shader(std::string vert, std::string frag, std::string geom = "");
    ObjData model(std::string raw);
    ptr<ui::Font> font(bytes raw, unsigned int size);
    ptr<core::Material> material(std::string raw);
}
