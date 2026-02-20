#include <q3d/phys/transform.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace q3d::phys;

AABB Transform::aabb() const {
	glm::vec3 half = scale_fac * 0.5f;

	glm::mat4 rot(1.0f);
	rot = glm::rotate(rot, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rot = glm::rotate(rot, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rot = glm::rotate(rot, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::vec3 corners[8];
	int i = 0;
	for (int xi = -1; xi <= 1; xi += 2) {
		for (int yi = -1; yi <= 1; yi += 2) {
			for (int zi = -1; zi <= 1; zi += 2) {
				glm::vec3 local = glm::vec3(half.x * xi, half.y * yi, half.z * zi);
				glm::vec3 rotated = glm::vec3(rot * glm::vec4(local, 1.0f));
				corners[i++] = rotated + position;
			}
		}
	}

	glm::vec3 mn = corners[0];
	glm::vec3 mx = corners[0];
	for (int j = 1; j < 8; j++) {
		mn = glm::min(mn, corners[j]);
		mx = glm::max(mx, corners[j]);
	}

	return AABB(mn, mx);
}

void Transform::translate(glm::vec3 delta) {
    position += delta;
}

void Transform::rotate(glm::vec3 delta) {
    rotation += delta;
}

void Transform::scale(glm::vec3 delta) {
    scale_fac += delta;
}

glm::mat4 Transform::getModelMatrix() const {
    auto mat = glm::mat4(1.f);

    mat = glm::translate(mat, position);

    mat = glm::rotate(mat, glm::radians(rotation.x), {1,0,0});
    mat = glm::rotate(mat, glm::radians(rotation.y), {0,1,0});
    mat = glm::rotate(mat, glm::radians(rotation.z), {0,0,1});

    mat = glm::scale(mat, scale_fac);

	return mat;
}