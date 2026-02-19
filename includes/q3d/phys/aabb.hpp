#pragma once

#include <glm/vec3.hpp>
#include <glm/common.hpp>

namespace q3d {
    namespace phys {
        class AABB {
        public:
            glm::vec3 min;
            glm::vec3 max;

            AABB()
                : min(std::numeric_limits<float>::max()),
                max(std::numeric_limits<float>::lowest()) {}

            AABB(const glm::vec3& min_, const glm::vec3& max_)
                : min(glm::min(min_, max_)),
                max(glm::max(min_, max_)) {}

            bool isValid() const;

            glm::vec3 size() const;

            glm::vec3 center() const;

            bool intersects(const AABB& other) const;

            bool contains(const glm::vec3& point) const;

            float volume() const;
        };
    }
}