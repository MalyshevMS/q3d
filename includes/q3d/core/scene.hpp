#pragma once

#include <string_view>
#include <unordered_map>
#include <q3d/res/ptr.hpp>

namespace q3d::core {

class Object;

class Scene {
protected:
    std::unordered_map<std::string, ptr<Object>> objects = {};
public:
    virtual void add(std::string_view name, ptr<Object> obj);
    void remove(std::string_view name);
    ptr<Object> get(std::string_view name);
    ptr<Object> operator[](std::string_view name) { return get(name); }

    template<class T, class... Args>
    ptr<T> create(std::string_view name, Args&&... args) {
        auto obj = std::make_shared<T>(std::forward<Args>(args)...);
        add(name, obj);
        return obj;
    }

    virtual void render() const;
};

} // namespace q3d::core
