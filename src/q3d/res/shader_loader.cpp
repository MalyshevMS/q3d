#include <q3d/res/loaders.hpp>
#include <q3d/res/resources.hpp>
#include <q3d/gl/shader.hpp>

using namespace q3d;
using namespace gl;

ptr<Shader> loader::shader(std::string vert, std::string frag, std::string geom) {
    return std::make_shared<gl::Shader>(vert, frag, geom);
}

ptr<Shader> ResourceManager::loadShader(const std::string& name, const fs::path& vert, const fs::path& frag, const fs::path& geom) {
    std::string geom_src;
    if (!geom.empty()) {
        geom_src = fs::readFile(geom);
    }

    auto shad = loader::shader(fs::readFile(vert), fs::readFile(frag), geom_src);

    const auto& shader = shaders.emplace(
        name, std::move(shad)
    );

    if (!shader.second) {
        log::error("ResourceManager::loadShader('{}'): Failed to emplace shader!", name);
    }

    log::info("Loaded shader '{}'", name);

    return shader.first->second;
}
