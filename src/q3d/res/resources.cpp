#include <q3d/res/resources.hpp>
#include <q3d/log/log.hpp>
#include <fstream>
#include <sstream>

q3d::Resources::Resources(std::string_view exePath) {
    auto found = exePath.find_last_of("/\\");
    path = exePath.substr(0, ++found);
}

q3d::Resources *q3d::Resources::getInstance(std::string_view exePath) {
    if (instance == nullptr) instance = new Resources { std::move(exePath) };
    return instance;
}

std::string q3d::Resources::readFile(std::string_view path) {
    std::string fpath = this->path + std::string(path);

    std::ifstream ifs;
    ifs.open(fpath, std::ios::in | std::ios::binary);
    if (!ifs.is_open()) {
        log::warn("Failed to open file '{}'!", fpath);
        return {};
    }

    std::ostringstream oss;
    oss << ifs.rdbuf();

    return oss.str();
}