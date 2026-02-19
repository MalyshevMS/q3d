#include <q3d/phys/aabb.hpp>

using namespace q3d::phys;

bool AABB::isValid() const {
    return min.x <= max.x &&
        min.y <= max.y &&
        min.z <= max.z;
}

glm::vec3 AABB::size() const {
    return max - min;
}

glm::vec3 AABB::center() const {
    return (min + max) * 0.5f;
}

bool q3d::phys::AABB::intersects(const AABB &other) const {
    return (min.x <= other.max.x && max.x >= other.min.x) &&
           (min.y <= other.max.y && max.y >= other.min.y) &&
           (min.z <= other.max.z && max.z >= other.min.z);
}

bool q3d::phys::AABB::contains(const glm::vec3 &point) const {
    return (point.x >= min.x && point.x <= max.x) &&
           (point.y >= min.y && point.y <= max.y) &&
           (point.z >= min.z && point.z <= max.z);
}

float q3d::phys::AABB::volume() const {
    auto s = size();
    return s.x * s.y * s.z;
}