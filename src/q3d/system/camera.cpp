#include <q3d/system/camera.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/trigonometric.hpp>

void q3d::Camera::updateView() {
    float pitch = glm::radians(rotation.x);
    float yaw   = glm::radians(rotation.y);
    float roll  = glm::radians(rotation.z);

    glm::mat4 rot = glm::eulerAngleYXZ(yaw, pitch, roll);

    dir   = glm::normalize(glm::vec3(rot * glm::vec4(world::forward, 0)));
    right = glm::normalize(glm::vec3(rot * glm::vec4(world::right  , 0)));
    up    = glm::normalize(glm::vec3(rot * glm::vec4(world::up     , 0)));

    view = glm::lookAt(position, position + dir, up);
}

void q3d::Camera::updateProj() {
    using enum Type;

    switch (type) {
        case Perspective: {
            proj = glm::perspective(glm::radians(fov), aspect, near, far);
        } break;

        case Orthographic: {
            proj = glm::ortho(
                -aspect * near, aspect * near,  // left, right
                -near, near,                    // top, bootom
                near, far                       // near, far
            );
        } break;
    }
}

q3d::Camera::Camera(float aspect, float fov, Type type)
 : position(0.f), rotation(0.f), aspect(aspect), fov(fov), type(type) {
    updateView();
    updateProj();
}

void q3d::Camera::setPosition(glm::vec3 pos) {
    position = pos;
    updateView();
}

void q3d::Camera::setRotation(glm::vec3 rot) {
    rotation = rot;
    updateView();
}

void q3d::Camera::set(glm::vec3 pos, glm::vec3 rot) {
    position = pos;
    rotation = rot;
    updateView();
}

void q3d::Camera::setFov(float fov) {
    this->fov = fov;
    updateProj();
}

void q3d::Camera::moveForward(float delta) {
    position += dir * delta;
    updateView();
}

void q3d::Camera::moveRight(float delta) {
    position += right * delta;
    updateView();
}

void q3d::Camera::moveUp(float delta) {
    position += up * delta;
    updateView();
}

void q3d::Camera::rotate(glm::vec3 delta) {
    rotation += delta;
    updateView();
}

void q3d::Camera::moveRotate(glm::vec3 deltaMove, glm::vec3 deltaRotate) {
    position += right   * deltaMove.x;
    position += up      * deltaMove.y;
    position += dir     * deltaMove.z;
    rotation += deltaRotate;
    updateView();
}