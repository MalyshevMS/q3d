#pragma once

#include <string_view>
#include <unordered_map>
#include <concepts>
#include <q3d/res/ptr.hpp>
#include <q3d/core/light_manager.hpp>

namespace q3d::core {

class Object;

class Scene {
protected:
    std::unordered_map<std::string, ptr<Object>> objects = {};
    std::unordered_map<std::string, ptr<object::Light>> lights = {};
public:
    virtual void add(std::string_view name, ptr<Object> obj);
    void remove(std::string_view name);
    ptr<Object> get(std::string_view name);
    ptr<Object> operator[](std::string_view name) { return get(name); }

    virtual void addLight(std::string_view name, ptr<object::Light> light);
    virtual void removeLight(std::string_view name);
    ptr<object::Light> getLight(std::string_view name);

    template<class T, class... Args>
    requires std::derived_from<T, core::Object>
    ptr<T> create(std::string_view name, Args&&... args) {
        auto obj = std::make_shared<T>(std::forward<Args>(args)...);
        add(name, obj);
        return obj;
    }

    virtual void render() const;
};

} // namespace q3d::core
