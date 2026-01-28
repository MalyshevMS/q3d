#pragma once

#include <string_view>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace q3d {
    namespace gl {
        

        class Shader {
        public:
            enum class Type {
                Vertex, Fragment
            };
        private:
            static bool compileShader(std::string_view src, const Type type, unsigned int& id);

            bool _isLinked = false;
            bool attachedFS = false;
            bool attachedVS = false;
            unsigned int id;
        public:
            static unsigned int typeToGl(Type type);

            void init();

            Shader() { init(); }
            Shader(std::string_view vert_src, std::string_view frag_src);
            ~Shader();

            bool isLinked() { return this->_isLinked; }

            unsigned int attach(std::string_view src, const Type type);
            void link();

            void use();
            static void unuse();

            int locate(std::string_view name);

            void uniform(std::string_view name, bool val);
            void uniform(std::string_view name, int val);
            void uniform(std::string_view name, float val);
            void uniform(std::string_view name, glm::vec2 val);
            void uniform(std::string_view name, glm::vec3 val);
            void uniform(std::string_view name, glm::mat4 val);
            
            // TODO: сделать uniform array
        };
    }
}