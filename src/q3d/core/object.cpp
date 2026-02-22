#include <q3d/core/object.hpp>
#include <q3d/core/active_camera.hpp>

using namespace q3d::core;

void Object::draw() const {
    if (!doDraw) [[unlikely]] return;

    for (const auto& f : features) gl::enable(f); // Enable all user's features

    auto& camera = ActiveCamera::getInstance()->cam();

    glm::mat4 mvp = camera.getMatrix() * transform.getModelMatrix();

    shader->use();

    if (texture) texture->use(*shader);

    shader->uniform("u_mvp", mvp);
    vao->draw();

    shader->unuse();

    for (const auto& f : features) gl::disable(f); // Disable for future drawings
}