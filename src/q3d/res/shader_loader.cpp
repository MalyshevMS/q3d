#include <q3d/res/resources.hpp>
#include <q3d/gl/shader.hpp>

using namespace q3d;
using namespace gl;

ptr<Shader> ResourceManager::loadShader(const std::string& name, const fs::path& vert, const fs::path& frag, const fs::path& geom) {
    auto vert_src = fs::readFile(vert);
    auto frag_src = fs::readFile(frag);
    std::string geom_src = "";

    if (!geom.empty()) {
        geom_src = fs::readFile(geom);
    }

    const auto& shader = shaders.emplace(
        name, std::make_shared<gl::Shader>(vert_src, frag_src, geom_src)
    );

    if (!shader.second) {
        log::error("ResourceManager::loadShader('{}'): Failed to emplace shader!", name);
    }

    log::info("Loaded shader '{}'", name);

    return shader.first->second;
}
