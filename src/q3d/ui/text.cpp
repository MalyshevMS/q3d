#include "q3d/gl/features.hpp"
#include <q3d/ui/text.hpp>
#include <q3d/core/active_camera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <string>

using namespace q3d;
using namespace ui;

Text::Text(ptr<gl::Shader> shader, ptr<Font> font, const std::string& text, phys::Transform transform, core::Color color)
 : core::Object(shader, nullptr, transform), text(text), font(font), color(color) {
    const float vertices[] = {
    //   X    Y          U    V
        0.f, 0.f,       0.f, 1.f,
        1.f, 0.f,       1.f, 1.f,
        1.f, 1.f,       1.f, 0.f,
        0.f, 1.f,       0.f, 0.f,
    };

    const unsigned int ind[] = {
        0, 2, 1,
        0, 3, 2,
    };

    vbo = std::make_unique<gl::Vbo>(vertices, sizeof(vertices), gl::buffer::Layout::l_xyzw);
    ibo = std::make_unique<gl::Ibo>(ind, 6);
    vao = std::make_unique<gl::Vao>();

    vao->addVbo(*vbo);
    vao->setIbo(*ibo);

    features[gl::feature::cullFace] = false;
}

void Text::draw() const {
    if (!doDraw) [[unlikely]] return;

    for (const auto& [f, b] : features) {
        if (b) gl::enable(f);
        else gl::disable(f);
    }

    auto camera = core::ActiveCamera::get();
    shader->use();

    shader->uniform("u_color", glm::vec3(color.r, color.g, color.b));

    const float startX = transform.position.x;
    float xc = startX;
    float yc = transform.position.y;

    float lineHeight = font->getc('H').size.y * 1.2f; 

    for (size_t i = 0; i < text.length(); ) {
        unsigned char cp = text[i];
        wchar_t unicode_char = 0;
        size_t bytes = 0;

        if (cp <= 0x7F) { unicode_char = cp; bytes = 1; }
        else if ((cp & 0xE0) == 0xC0) { unicode_char = cp & 0x1F; bytes = 2; }
        else if ((cp & 0xF0) == 0xE0) { unicode_char = cp & 0x0F; bytes = 3; }
        else if ((cp & 0xF8) == 0xF0) { unicode_char = cp & 0x07; bytes = 4; }
        else { i++; continue; }

        if (i + bytes > text.length()) break;

        for (size_t j = 1; j < bytes; j++) {
            unicode_char = (unicode_char << 6) | (text[i + j] & 0x3F);
        }
        i += bytes;

        if (unicode_char == L'\n') {
            xc = startX;
            yc -= lineHeight;
            continue;
        }
        if (unicode_char == L'\r') {
            continue;
        }
        if (unicode_char == L'\t') {
            xc += font->getc(' ').advance >> 4;
            continue;
        }

        auto ch = font->getc(unicode_char);

        float xPos = xc + ch.bearing.x;
        float yPos = yc - (ch.size.y - ch.bearing.y);

        float w = ch.size.x;
        float h = h = ch.size.y;

        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(xPos, yPos, 0.f));
        model = glm::scale(model, glm::vec3(w, h, 1.f));
        shader->uniform("u_mvp", camera.getMatrix() * model);

        ch.texture->use(*shader);
        vao->draw();

        xc += (ch.advance >> 6);
    }

    vao->unbind();
    gl::Texture::unbind();
    shader->unuse();
}
