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
        glm::vec2 fb_size;
        std::string title;

        float deltaTime;
        float currentTime;
        float lastTime;
    public:
        Window(std::string_view title, glm::vec2 size);

        bool isOpen();
        void close();
        static void terminate();

        void update();

        /// getters / setters

        glm::vec2 getSize() { return size; }
        void setSize(glm::vec2 size);

        glm::vec2 getFBSize();

        std::string getTitle() { return title; }
        void setTitle(std::string_view title);

        float getAspectRatio() { return size.x / size.y; };
        float getInversedAspectRatio() { return size.y / size.x; };

        float getDeltaTime() { return deltaTime; };
    };
}