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

    handle = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);

    if (!handle) {
        log::error("glfwCreateWindow failed");
        terminate();
        return;
    }

    this->size  = size;
    this->title = title;
    this->fb_size = getFBSize();

    glfwMakeContextCurrent(handle);
    glfwSetWindowUserPointer(handle, this);
    
    glfwSetWindowSizeCallback(handle, __q3d_window_size_cb); // TODO: сделать возможность добавлять свой callback

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        log::error("gladLoadGLLoader failed");
        terminate();
        return;
    }

    glViewport(0, 0, fb_size.x, fb_size.y);
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

    glfwSetWindowSize(handle, size.x, size.y);

    this->size = size;
    this->fb_size = getFBSize();

    glViewport(0, 0, fb_size.x, fb_size.y);
}

void q3d::Window::setTitle(std::string_view title) {
    this->title = title;
    glfwSetWindowTitle(handle, title.data());
}

glm::vec2 q3d::Window::getFBSize() {
    int x, y;
    glfwGetFramebufferSize(handle, &x, &y);
    return {x, y};
}