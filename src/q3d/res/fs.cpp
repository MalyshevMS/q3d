#include <q3d/res/fs.hpp>
#include <q3d/log/log.hpp>

#if defined(__linux__)
    #include <unistd.h>
    #include <limits.h>
#elif defined(_WIN32)
    #include <Windows.h>
#endif

#include <fstream>

namespace q3d::fs {

path getExecutableDir() {
#if defined(__linux__)
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);

    if (count != -1) {
        return path(std::string(result, count)).parent_path();
    }
#elif defined(_WIN32)
    char result[MAX_PATH];
    GetModuleFileNameA(NULL, result, MAX_PATH);
    return path(result).parent_path();
#endif

    return current_path();
}

path resolve(const path& relative) {
    if (relative.is_absolute()) return relative;

    return getExecutableDir() / relative;
}

std::string readFile(const path& filepath) {
    auto path = resolve(filepath);
    std::ifstream ifs;
    ifs.open(path, std::ios::in | std::ios::binary);
    if (!ifs.is_open()) {
        log::warn("fs::readFile('{}'): Failed to open file '{}'!", filepath.string(), path.string());
        return {};
    }

    std::ostringstream oss;
    oss << ifs.rdbuf();

    return oss.str();
}

} // namespace q3d::fs
