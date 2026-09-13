#pragma once

#include <vector>
#include <cstdint>
#include <string_view>
#include <string>
#include <unordered_map>
#include <q3d/res/fs.hpp>

namespace q3d::vfs {

struct FileBuffer {
    std::vector<uint8_t> data;

    [[nodiscard]] std::string_view asStringView() const {
        return {
            reinterpret_cast<const char*>(data.data()), data.size()
        };
    }
};

class VFS {
private:
    std::vector<uint8_t> decompressZstd(const std::vector<uint8_t>& compressed);

    bool parseTar(const std::vector<uint8_t>& tar);

    std::unordered_map<std::string, FileBuffer> files;
public:
    VFS() = default;
    ~VFS() = default;

    bool openArchive(const fs::path& path);

    [[nodiscard]] std::optional<FileBuffer> readFile(const std::string& internalPath) const;

    [[nodiscard]] bool hasFile(const std::string& internalPath) const;

    [[nodiscard]] std::vector<std::string> listFiles() const;
};

} // namespace q3d::vfs
