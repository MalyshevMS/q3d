#pragma  once

#include <q3d/core/color.hpp>
#include <q3d/core/object.hpp>
#include <q3d/ui/font.hpp>
#include <string>

namespace q3d {
    namespace ui {
        class Text : public core::Object {
        private:
            std::string text;
            ptr<Font> font;
            core::Color color = core::Color::White;
        public:
            Text(ptr<gl::Shader> shader, ptr<Font> font, const std::string& text, phys::Transform transform = {}, core::Color color = core::Color::White);

            void draw() const override;

            void setText(const std::string& newText) { text = newText; }
            void setColor(core::Color newColor) {
                color.r = newColor.r;
                color.g = newColor.g;
                color.b = newColor.b;
                color.a = newColor.a;
            }
        };
    }
}
