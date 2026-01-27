#include <glad/glad.h>
#include <q3d/window/window.hpp>
#include <q3d/log/log.hpp>

void __q3d_window_size_cb(GLFWwindow* w, int x, int y) {
    auto win = *static_cast<q3d::Window*>(glfwGetWindowUserPointer(w));
    win.setSize({x, y});
}

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
        terminate();
        return;
    }

    this->size  = size;
    this->title = title;

    glfwMakeContextCurrent(handle);
    glfwSetWindowUserPointer(handle, this);
    
    glfwSetWindowSizeCallback(handle, __q3d_window_size_cb); // TODO: сделать возможность добавлять свой callback

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        log::error("gladLoadGLLoader failed");
        terminate();
        return;
    }
}

bool q3d::Window::isOpen() {
    if (!handle) return false;
    return !glfwWindowShouldClose(handle);
}

void q3d::Window::close() {
    if (!handle) return;
    glfwSetWindowShouldClose(handle, GLFW_TRUE);
}

void q3d::Window::terminate() {
    glfwTerminate();
}

void q3d::Window::update() {
    if (!handle) return;

    glfwSwapBuffers(handle);
    glfwPollEvents();
}

void q3d::Window::setSize(glm::vec2 size) {
    if (!handle) return;

    this->size = size;
    glfwSetWindowSize(handle, size.x, size.y);
    glViewport(0, 0, size.x, size.y);
}

void q3d::Window::setTitle(std::string_view title) {
    this->title = title;
    glfwSetWindowTitle(handle, title.cbegin());
}