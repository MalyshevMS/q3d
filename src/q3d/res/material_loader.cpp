#include <q3d/res/resources.hpp>
#include <q3d/core/material.hpp>
#include <nlohmann/json.hpp>

using namespace q3d;
using namespace core;

using json = nlohmann::json;

ptr<Material> ResourceManager::loadMaterial(const std::string& name, const fs::path& path) {
    auto content = fs::readFile(path);

    json j = json::parse(content);

    auto mat = std::make_shared<core::Material>();

    mat->ambient.r = j["ambient"][0];
    mat->ambient.g = j["ambient"][1];
    mat->ambient.b = j["ambient"][2];

    mat->diffuse.r = j["diffuse"][0];
    mat->diffuse.g = j["diffuse"][1];
    mat->diffuse.b = j["diffuse"][2];

    mat->specular.r = j["specular"][0];
    mat->specular.g = j["specular"][1];
    mat->specular.b = j["specular"][2];

    mat->shininess = j["shininess"];

    const auto& material = materials.emplace(
        name, mat
    );

    if (!material.second) {
        log::error("ResourceManager::loadMaterial('{}'): failed to emplace material", name);
        return nullptr;
    }

    log::info("Loaded material '{}'", name);

    return material.first->second;
}

