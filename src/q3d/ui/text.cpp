#include <q3d/ui/text.hpp>
#include <q3d/core/active_camera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

using namespace q3d::ui;

Text::Text(ptr<gl::Shader> shader, ptr<Font> font, const std::string& text, phys::Transform transform, core::Color color)
 : core::Object(shader, transform), text(text), font(font), color(color) {
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
}

void Text::draw() const {
    if (!doDraw) [[unlikely]] return;

    for (const auto& f : features) gl::enable(f);

    auto camera = core::ActiveCamera::get();

    shader->use();

    shader->uniform("u_texture", 0);
    shader->uniform("u_color", glm::vec3(color.r, color.g, color.b));

    float xc = transform.position.x;
    float yc = transform.position.y;

    for (const auto& c : text) {
        auto ch = font->getc(c);

        float xPos = xc + ch.bearing.x;
        float yPos = yc + (ch.size.y - ch.bearing.y);

        float w = ch.size.x;
        float h = ch.size.y;

        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(xPos, yPos, 0.f));
        model = glm::scale(model, glm::vec3(w, h, 1.f));
        shader->uniform("u_mvp", camera.getMatrix() * model);

        ch.texture->bind();

        vao->draw();

        xc += (ch.advance >> 6);
    }

    vao->unbind();
    gl::Texture::unbind();
    shader->unuse();

    for (const auto& f : features) gl::disable(f);
}
