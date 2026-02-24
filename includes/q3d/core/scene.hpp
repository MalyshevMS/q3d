#pragma once

#include <string_view>
#include <unordered_map>
#include <q3d/res/ptr.hpp>

namespace q3d {
    namespace core {
        class Object;

        class Scene {
        private:
            std::unordered_map<std::string, ptr<Object>> objects;
        public:
            void add(std::string_view name, ptr<Object> obj);
            void remove(std::string_view name);
            ptr<Object> get(std::string_view name);
            ptr<Object> operator[](std::string_view name) { return get(name); }

            void render();
        };
    }
}