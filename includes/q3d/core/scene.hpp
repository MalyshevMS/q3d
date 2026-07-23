#pragma once

#include <string_view>
#include <unordered_map>
#include <concepts>
#include <q3d/res/ptr.hpp>
#include <q3d/obj/light/light.hpp>
#include <q3d/gl/ssbo.hpp>

namespace q3d::core {

class Object;

class Scene {
protected:
    std::unordered_map<std::string, ptr<Object>> objects = {};

    std::unordered_map<std::string, ptr<object::DirLight>> dirLights = {};
    std::unordered_map<std::string, ptr<object::PointLight>> pointLights = {}; // for future
    std::unordered_map<std::string, ptr<object::SpotLight>> spotLights = {};

    gl::Ssbo dirLightSsbo = gl::Ssbo(0);
    gl::Ssbo pointLightSsbo = gl::Ssbo(1);
    gl::Ssbo spotLightSsbo = gl::Ssbo(2);
public:
    virtual void add(std::string_view name, ptr<Object> obj);
    void remove(std::string_view name);
    ptr<Object> get(std::string_view name);
    ptr<Object> operator[](std::string_view name) { return get(name); }

    template<class T, class... Args>
    requires std::derived_from<T, core::Object>
    ptr<T> create(std::string_view name, Args&&... args) {
        auto obj = std::make_shared<T>(std::forward<Args>(args)...);
        add(name, obj);
        return obj;
    }

    void addDirLight(std::string_view name, const object::DirLight& light);
    void addPointLight(std::string_view name, const object::PointLight& light);
    void addSpotLight(std::string_view name, const object::SpotLight& light);

    ptr<object::DirLight>   getDirLight(std::string_view name);
    ptr<object::PointLight> getPointLight(std::string_view name);
    ptr<object::SpotLight>  getSpotLight(std::string_view name);

    void removeDirLight(std::string_view name);

    virtual void render();
};

} // namespace q3d::core
