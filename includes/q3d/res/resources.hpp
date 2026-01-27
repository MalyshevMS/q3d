#pragma once

#include <string>
#include <string_view>

namespace q3d {
    /// @warning SINGLETONE!!!
    class Resources {
    private:
        Resources(std::string_view exePath);
        static Resources* instance;

        std::string path;
    public:
        // some singletone...
        Resources(const Resources&) = delete;
        Resources& operator=(const Resources&) = delete;
        static Resources* getInstance(std::string_view exePath);

        std::string getExePath() { return path; }

        std::string readFile(std::string_view path);
    };
}