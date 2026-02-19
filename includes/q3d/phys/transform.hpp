#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <q3d/phys/aabb.hpp>

namespace q3d {
    namespace phys {
        class Transform {
        public:
            glm::vec3 position;
            glm::vec3 rotation;
            glm::vec3 scale_fac;

            Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale_fac)
                    : position(position), rotation(rotation), scale_fac(scale_fac) {};

            AABB aabb() const; // TODO: Create similar with linked AABB (and linked AABB also)

            void translate(glm::vec3 delta);
            void rotate(glm::vec3 delta);
            void scale(glm::vec3 delta);

            glm::mat4 getModelMatrix() const;
        };
    }
}