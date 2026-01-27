#pragma once

#include <string_view>

namespace q3d {
    namespace gl {
        class Shader {
        private:
            static bool compileShader(std::string_view src, const unsigned int type, unsigned int& id);

            bool _isLinked = false;
            bool attachedFS = false;
            bool attachedVS = false;
            unsigned int id;
        public:
            void init();

            Shader() { init(); }
            Shader(std::string_view vert_src, std::string_view frag_src);

            bool isLinked() { return this->_isLinked; }

            unsigned int attach(std::string_view src, const unsigned int type);
            void link();

            void use();
            static void unuse();

            // TODO: сделать uniform
        };
    }
}