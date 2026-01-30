#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <q3d/gl/texture.hpp>
#include <memory>

namespace q3d {
    /// @brief `std::shared_ptr`
    /// @tparam _Tp typename to store
    template<typename _Tp>
    using ptr = std::shared_ptr<_Tp>;

    /// @warning SINGLETONE!!!
    class Resources {
    private:
        Resources(std::string_view exePath);
        static Resources* instance;

        std::string path;

        // Maps Typenames

        using TextureMap = std::unordered_map<std::string, ptr<gl::Texture>>;

        // Maps

        TextureMap textures;
    public:
        // some singletone...
        Resources(const Resources&) = delete;
        Resources& operator=(const Resources&) = delete;
        static Resources* getInstance(std::string_view exePath);

        std::string getExePath() { return path; }

        std::string readFile(std::string_view path);

        ptr<gl::Texture> loadTexture(std::string_view name, std::string_view path);
        ptr<gl::Texture> getTexture(std::string_view name);
    };
}