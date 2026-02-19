#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace q3d {
    namespace world {
        static constexpr glm::vec3 up      = {  0.f,  1.f,  0.f };
        static constexpr glm::vec3 right   = {  1.f,  0.f,  0.f };
        static constexpr glm::vec3 forward = {  0.f,  0.f, -1.f };
    }

    class Camera {
    public:
        enum class Type {
            Perspective,
            Orthographic
        };
    private:
        Type type;

        glm::vec3 position;
        glm::vec3 rotation;
        
        glm::vec3 dir;
        glm::vec3 right;
        glm::vec3 up;

        glm::mat4 view;
        glm::mat4 proj;

        float aspect;
        float fov;
        float near = 0.001f;
        float far = 100.f;

        void updateView();
        void updateProj();
    public:
        Camera(float aspect, float fov = 90.f, Type type = Type::Perspective);

        void setPosition(glm::vec3 pos);
        void setRotation(glm::vec3 rot);
        void set(glm::vec3 pos, glm::vec3 rot);

        glm::vec3 getPosition() { return position; };
        glm::vec3 getRotation() { return rotation; };

        void setFov(float fov);
        float getFov() { return fov; }

        glm::mat4 getView() { return view; }
        glm::mat4 getProj() { return proj; }
        glm::mat4 getMatrix() { return proj * view; }

        void moveForward(float delta);
        void moveRight(float delta);
        void moveUp(float delta);
        void rotate(glm::vec3 delta);

        void moveRotate(glm::vec3 deltaMove, glm::vec3 deltaRotate);
    };
}