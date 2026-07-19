#include <q3d/core/camera.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/trigonometric.hpp>

using namespace q3d;
using namespace core;

void Camera::updateView() {
    float pitch = glm::radians(rotation.x);
    float yaw   = glm::radians(rotation.y);
    float roll  = glm::radians(rotation.z);

    glm::mat4 rot = glm::eulerAngleYXZ(yaw, pitch, roll);

    dir   = glm::normalize(glm::vec3(rot * glm::vec4(world::forward, 0)));
    right = glm::normalize(glm::vec3(rot * glm::vec4(world::right  , 0)));
    up    = glm::normalize(glm::vec3(rot * glm::vec4(world::up     , 0)));

    view = glm::lookAt(position, position + dir, up);
}

void Camera::updateProj() {
    using enum Type;

    switch (type) {
        case Perspective: {
            proj = glm::perspective(glm::radians(fov), aspect, near, far);
        } break;

        case Orthographic: {
            float w = aspect * fov; // using FOV as size
            float h = fov;
            proj = glm::ortho(-w, w, -h, h, near, far);
        } break;
    }
}

Camera::Camera(float aspect, float fov, Type type)
 : position(0.f), rotation(0.f), aspect(aspect), fov(fov), type(type) {
    updateView();
    updateProj();
}

void Camera::setPosition(glm::vec3 pos) {
    position = pos;
    updateView();
}

void Camera::setRotation(glm::vec3 rot) {
    rotation = rot;
    updateView();
}

void Camera::set(glm::vec3 pos, glm::vec3 rot) {
    position = pos;
    rotation = rot;
    updateView();
}

void Camera::setFov(float fov) {
    this->fov = fov;
    updateProj();
}

void Camera::setNear(float near) {
    this->near = near;
    updateProj();
}

void Camera::setFar(float far) {
    this->far = far;
    updateProj();
}

void Camera::setAspect(float aspect) {
    this->aspect = aspect;
    updateProj();
}

void Camera::moveForward(float delta) {
    position += dir * delta;
    updateView();
}

void Camera::moveRight(float delta) {
    position += right * delta;
    updateView();
}

void Camera::moveUp(float delta) {
    position += up * delta;
    updateView();
}

void Camera::rotate(glm::vec3 delta) {
    rotation += delta;
    updateView();
}

void Camera::move(glm::vec3 delta) {
    position += right * delta.x;
    position += up    * delta.y;
    position += dir   * delta.z;
    updateView();
}

void Camera::moveRotate(glm::vec3 deltaMove, glm::vec3 deltaRotate) {
    position += right   * deltaMove.x;
    position += up      * deltaMove.y;
    position += dir     * deltaMove.z;
    rotation += deltaRotate;
    updateView();
}
