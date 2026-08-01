#pragma once

#include <string_view>
#include <unordered_map>
#include <concepts>
#include <q3d/res/ptr.hpp>
#include <q3d/obj/light.hpp>
#include <q3d/gl/ssbo.hpp>
#include <q3d/gl/shader.hpp>
#include <q3d/gl/shadow_map.hpp>
#include <q3d/gl/cubemap.hpp>

namespace q3d::core {

class Object;

class Scene {
protected:
    std::unordered_map<std::string, ptr<Object>> objects = {};

    std::unordered_map<std::string, ptr<object::DirLightInternal>> dirLights = {};
    std::unordered_map<std::string, ptr<object::SpotLightInternal>> spotLights = {};
    std::unordered_map<std::string, ptr<object::PointLightInternal>> pointLights = {};

    gl::Ssbo dirLightSsbo = gl::Ssbo(0);
    gl::Ssbo spotLightSsbo = gl::Ssbo(1);
    gl::Ssbo pointLightSsbo = gl::Ssbo(2);

    gl::Ssbo lightSpaceMatricesSsbo = gl::Ssbo(3);

    ptr<gl::Shader> shadowShader = nullptr;
    ptr<gl::Shader> pointShadowShader = nullptr;

    uptr<gl::ShadowMap> shadowMap = nullptr;
    uptr<gl::CubeMap> cubeMap = nullptr;

    float pointShadowFarPlane = 100.f;
public:
    void initShadows(ptr<gl::Shader> depthShader, unsigned int resolution = 2048, unsigned int maxLights = 8);
    void initPointShadows(ptr<gl::Shader> pointDepthShader, unsigned int resolution = 2048, unsigned int maxLights = 8, float farPlane = 100.f);

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

    void addDirLight(std::string_view name, const object::DirLightInternal& light);
    void addSpotLight(std::string_view name, const object::SpotLightInternal& light);
    void addPointLight(std::string_view name, const object::PointLightInternal& light);

    ptr<object::DirLightInternal>   getDirLight(std::string_view name);
    ptr<object::SpotLightInternal>  getSpotLight(std::string_view name);
    ptr<object::PointLightInternal> getPointLight(std::string_view name);

    void removeDirLight(std::string_view name);

    virtual void render();
};

} // namespace q3d::core
