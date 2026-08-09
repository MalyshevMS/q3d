#include <q3d/core/scene.hpp>
#include <q3d/core/object.hpp>
#include <q3d/core/active_camera.hpp>
#include <q3d/gl/fbo.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <map>

using namespace q3d;
using namespace gl;
using namespace core;
using namespace object;

void Scene::initShadows(ptr<Shader> depthShader, unsigned int resolution, unsigned int maxLights) {
    shadowShader = depthShader;
    shadowMap = std::make_unique<ShadowMap>(resolution, maxLights);
}

void Scene::initPointShadows(ptr<Shader> pointDepthShader, unsigned int resolution, unsigned int maxLights, float farPlane) {
    pointShadowShader = pointDepthShader;
    cubeMap = std::make_unique<CubeMap>(resolution, maxLights);
    pointShadowFarPlane = farPlane;
}

void Scene::add(std::string_view name, ptr<Object> obj) {
    objects[name.data()] = obj;
}

void Scene::remove(std::string_view name) {
    objects.erase(name.data());
}

ptr<Object> Scene::get(std::string_view name) {
    auto it = objects.find(name.data());

    if (it != objects.end()) return it->second;
    return nullptr;
}

void Scene::addDirLight(std::string_view name, DirLight light) {
    dirLights[name.data()] = std::make_shared<DirLight>(std::move(light));
}

void Scene::addSpotLight(std::string_view name, SpotLight light) {
    spotLights[name.data()] = std::make_shared<SpotLight>(std::move(light));
}

void Scene::addPointLight(std::string_view name, const PointLightInternal& light) {
    pointLights[name.data()] = std::make_shared<PointLightInternal>(light);
}

ptr<DirLight> Scene::getDirLight(std::string_view name) {
    auto it = dirLights.find(name.data());

    if (it != dirLights.end()) return it->second;
    return nullptr;
}

ptr<PointLightInternal> Scene::getPointLight(std::string_view name) {
    auto it = pointLights.find(name.data());

    if (it != pointLights.end()) return it->second;
    return nullptr;
}

ptr<SpotLight> Scene::getSpotLight(std::string_view name) {
    auto it = spotLights.find(name.data());

    if (it != spotLights.end()) return it->second;
    return nullptr;
}

void Scene::render() {
    if (!dirLights.empty()) {
        std::vector<DirLightInternal> raw;
        raw.reserve(dirLights.size());

        for (const auto& [_, l] : dirLights) {
            raw.push_back(l->getInternal());
        }

        dirLightSsbo.updateData(std::span(raw));
    }

    if (!spotLights.empty()) {
        std::vector<SpotLightInternal> raw;
        raw.reserve(spotLights.size());

        for (const auto& [_, l] : spotLights) {
            raw.push_back(l->getInternal());
        }

        spotLightSsbo.updateData(std::span(raw));
    }

    if (!pointLights.empty()) {
        std::vector<PointLightInternal> raw;
        raw.reserve(pointLights.size());

        for (const auto& [_, l] : pointLights) {
            raw.push_back(*l);
        }

        pointLightSsbo.updateData(std::span(raw));
    }

    // PASS 1 - Shadows

    std::vector<glm::mat4> lightSpaceMatrices;
    lightSpaceMatrices.reserve(dirLights.size());

    int prevFbo = 0;
    int viewport[4];
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevFbo);
    glGetIntegerv(GL_VIEWPORT, viewport);

    enable(feature::cullFace);
    enable(feature::depthTest);
    glCullFace(GL_FRONT);

    // A) Directional lights and spot lights

    if (shadowMap && shadowShader) {
        size_t index = 0;

        shadowShader->use();

        if (!dirLights.empty()) {
            for (const auto& [_, l] : dirLights) {
                glm::vec3 pos  = -l->getInternal().direction * 25.f;
                glm::mat4 proj = glm::ortho(-35.f, 35.f, -35.f, 35.f, 0.1f, 100.f);
                glm::mat4 view = glm::lookAt(pos, glm::vec3(0.f), world::up);

                auto mat = proj * view;

                lightSpaceMatrices.push_back(mat);

                shadowMap->bindWrite(index);

                shadowShader->uniform("u_lightSpaceMatrix", mat);

                for (const auto& [_, o] : objects) {
                    if (!o->castShadows) continue;
                    shadowShader->uniform("u_model", o->transform.getModelMatrix());
                    o->drawGeometryOnly();
                }

                index++;
            }
        }

        if (!spotLights.empty()) {
            for (const auto& [_, l] : spotLights) {
                const auto& internal = l->getInternal();
                glm::vec3 pos  = internal.position;
                float fov = 2.f * std::acos(internal.outerCutOff);
                glm::mat4 proj = glm::perspective(fov, 1.f, 0.1f, 100.f);
                glm::vec3 up = world::up;
                if (glm::abs(glm::dot(internal.direction, up)) > 0.99f) up = world::forward;
                glm::mat4 view = glm::lookAt(pos, pos + internal.direction, up);

                auto mat = proj * view;

                lightSpaceMatrices.push_back(mat);

                shadowMap->bindWrite(index);

                shadowShader->uniform("u_lightSpaceMatrix", mat);

                for (const auto& [_, o] : objects) {
                    if (!o->castShadows) continue;
                    shadowShader->uniform("u_model", o->transform.getModelMatrix());
                    o->drawGeometryOnly();
                }

                index++;
            }
        }

        lightSpaceMatricesSsbo.updateData(std::span(lightSpaceMatrices));
    }

    // B) Point lights

    if (cubeMap && pointShadowShader && !pointLights.empty()) {
        pointShadowShader->use();
        cubeMap->clear();

        glm::mat4 proj = glm::perspective(glm::radians(90.f), 1.f, 0.1f, pointShadowFarPlane);


        size_t index = 0;

        for (const auto& [_, l] : pointLights) {
            glm::vec3 pos = l->position;

            std::array<glm::mat4, 6> shadowTransforms = {
                proj * glm::lookAt(pos, pos + world::right, -world::up),
                proj * glm::lookAt(pos, pos - world::right, -world::up),
                proj * glm::lookAt(pos, pos + world::up, -world::forward),
                proj * glm::lookAt(pos, pos - world::up, world::forward),
                proj * glm::lookAt(pos, pos - world::forward, -world::up),
                proj * glm::lookAt(pos, pos + world::forward, -world::up),
            };

            cubeMap->bindWrite(index);

            pointShadowShader->uniform("u_lightSpaceMatrices", std::span(shadowTransforms));
            pointShadowShader->uniform("u_lightIndex", static_cast<int>(index));
            pointShadowShader->uniform("u_lightPos", pos);
            pointShadowShader->uniform("u_farPlane", pointShadowFarPlane);

            for (const auto& [_, o] : objects) {
                if (!o->castShadows) continue;
                pointShadowShader->uniform("u_model", o->transform.getModelMatrix());
                o->drawGeometryOnly();
            }

            index++;
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, prevFbo);
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

    // PASS 2 - Main render

    glCullFace(GL_BACK);
    if (shadowMap) shadowMap->bindRead();
    if (cubeMap) cubeMap->bindRead();

    using Order = std::map<float, ptr<Object>>;
    Order sorted;
    for (const auto& [_, obj] : objects) {
        float distance = glm::length(
            ActiveCamera::get().getPosition() - obj->transform.position
        );
        sorted[distance] = obj;
    }

    for (auto it = sorted.rbegin(); it != sorted.rend(); it++) {
        if (it->second) {
            it->second->draw();
        }
    }

    for (const auto& [_, l] : dirLights) {
        if (l) {
            l->draw();
        }
    }

    for (const auto& [_, l] : spotLights) {
        if (l) {
            l->draw();
        }
    }
}
