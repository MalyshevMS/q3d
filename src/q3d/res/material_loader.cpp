#include <q3d/res/loaders.hpp>
#include <q3d/res/resources.hpp>
#include <q3d/core/material.hpp>
#include <nlohmann/json.hpp>

using namespace q3d;
using namespace core;

using json = nlohmann::json;

ptr<Material> loader::material(std::string raw) {
    json j = json::parse(raw);

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

    return mat;
}

ptr<Material> ResourceManager::loadMaterial(const std::string& name, const fs::path& path) {
    auto mat = loader::material(fs::readFile(path));

    const auto& material = materials.emplace(
        name, std::move(mat)
    );

    if (!material.second) {
        log::error("ResourceManager::loadMaterial('{}'): failed to emplace material", name);
        return nullptr;
    }

    log::info("Loaded material '{}'", name);

    return material.first->second;
}

