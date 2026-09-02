#pragma once

#include <filesystem>

namespace q3d::fs {

using namespace std::filesystem;

path getExecutableDir();
path resolve(const path& relative);
std::string readFile(const path& filepath);

} // namespace q3d::fs
