#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <string>
#include <string_view>

namespace q3d {
    class Window {
    private:
        GLFWwindow* handle;

        glm::vec2 size;
        std::string title;
    public:
        Window(std::string_view title, glm::vec2 size);

        bool isOpen();
        void close();
        static void terminate();

        void update();

        /// getters / setters

        glm::vec2 getSize() { return size; }
        void setSize(glm::vec2 size);

        std::string getTitle() { return title; }
        void setTitle(std::string_view title);
    };
}