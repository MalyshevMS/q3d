#include <glad/glad.h>
#include <q3d/window/window.hpp>
#include <q3d/log/log.hpp>

q3d::Window::Window(std::string_view title, glm::vec2 size) {
    if (!glfwInit()) {
        log::error("glfwInit failed");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(size.x, size.y, title.cbegin(), nullptr, nullptr);

    if (!handle) {
        log::error("glfwCreateWindow failed");
        return;
    }
}