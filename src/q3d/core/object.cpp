#include <q3d/core/object.hpp>
#include <q3d/gl/ssbo.hpp>
#include <q3d/obj/light/light.hpp>
#include <q3d/core/active_camera.hpp>

using namespace q3d;
using namespace core;
using namespace object;
using namespace gl;

void Object::draw() const {
    if (!doDraw) [[unlikely]] return;

    for (const auto& [f, b] : features) {
        if (b) enable(f);
        else disable(f);
    }

    const auto& camera = ActiveCamera::get();
    const auto model = transform.getModelMatrix();
    const glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));

    shader->use();

    if (texture) texture->use(*shader);
    if (material) material->use(*shader);

    shader->uniform("u_model", model);
    shader->uniform("u_viewProjection", camera.getMatrix());
    shader->uniform("u_normalMatrix", normalMatrix);
    shader->uniform("u_viewPos", camera.getPosition());
    shader->uniform("u_shadowMap", 1);

    vao->draw();

    shader->unuse();
}

void Object::drawGeometryOnly() const {
    if (!doDraw) [[unlikely]] return;
    if (vao) vao->draw();
}
