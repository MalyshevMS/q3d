#include <q3d/core/object.hpp>
#include <q3d/core/active_camera.hpp>

using namespace q3d;
using namespace core;

void Object::draw(LightManager& lm) const {
    if (!doDraw) [[unlikely]] return;

    for (const auto& [f, b] : features) {
        if (b) gl::enable(f);
        else gl::disable(f);
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

    // You should get it from scene, but it's ok for the first time
    // shader->uniform("u_dirLight.direction", glm::vec3(-1.f));
    // shader->uniform("u_dirLight.ambient", glm::vec3(0.9f));
    // shader->uniform("u_dirLight.diffuse", glm::vec3(0.8f));
    // shader->uniform("u_dirLight.specular", glm::vec3(1.f));

    lm.updateBuffers(*shader);

    vao->draw();

    shader->unuse();
}
