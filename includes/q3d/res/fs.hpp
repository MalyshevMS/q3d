#pragma once

#include <filesystem>
#include <q3d/res/ptr.hpp>

namespace q3d::fs {

using namespace std::filesystem;

path getExecutableDir();
path resolve(const path& relative);
std::string readFile(const path& filepath);
bytes readFileBytes(const path& filepath);

} // namespace q3d::fs
