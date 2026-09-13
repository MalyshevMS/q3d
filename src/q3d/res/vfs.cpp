#include <q3d/res/vfs.hpp>
#include <q3d/log/log.hpp>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <zstd.h>

using namespace q3d;
using namespace vfs;

static size_t parseOctal(const char* str, size_t maxLen) {
    size_t result = 0;
    for (size_t i = 0; i < maxLen && str[i] >= '0' && str[i] <= '7'; i++) {
        result = (result << 3) + (str[i] - '0');
    }

    return result;
}

bool VFS::openArchive(const fs::path& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        log::error("VFS::openArchive('{}'): Failed to open archive file", path.string());
        return false;
    }

    auto size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> compressed(size);

    if (!file.read(reinterpret_cast<char*>(compressed.data()), size)) {
        log::error("VFS::openArchive('{}'): Failed to read data from archive file", path.string());
        return false;
    }

    auto tar = decompressZstd(compressed);

    if (tar.empty()) return false;

    return parseTar(tar);
}

std::vector<uint8_t> VFS::decompressZstd(const std::vector<uint8_t>& compressed) {
    const auto size = ZSTD_getFrameContentSize(compressed.data(), compressed.size());

    if (size == ZSTD_CONTENTSIZE_ERROR) {
        log::error("VFS::decompressZstd(): Not compressed by zstd");
        return {};
    }
    if (size == ZSTD_CONTENTSIZE_UNKNOWN) {
        log::error("VFS::decompressZstd(): Original size unknown");
        return {};
    }

    std::vector<uint8_t> buffer(size);

    const size_t result = ZSTD_decompress(buffer.data(), buffer.size(), compressed.data(), compressed.size());

    if (ZSTD_isError(result)) {
        log::error("VFS::decompressZstd(): Decompression error: {}", ZSTD_getErrorName(result));
        return {};
    }

    return buffer;
}

bool VFS::parseTar(const std::vector<uint8_t>& tar) {
    size_t offset = 0;
    size_t totalSize = tar.size();

    while (offset + 512 <= totalSize) {
        const uint8_t* header = tar.data() + offset;

        if (header[0] == '\0') {
            break;
        }

        std::string fileName(reinterpret_cast<const char*>(header), strnlen(reinterpret_cast<const char*>(header), 100));

        size_t fileSize = parseOctal(reinterpret_cast<const char*>(header + 124), 12);

        char typeFlag = header[156];

        offset += 512;

        if (typeFlag == '0' || typeFlag == '\0') {
            if (fileName.rfind("./", 0) == 0) {
                fileName = fileName.substr(2);
            } else if (fileName.rfind("/", 0) == 0) {
                fileName = fileName.substr(1);
            }

            if (!fileName.empty() && offset + fileSize <= totalSize) {
                FileBuffer buffer;
                buffer.data.assign(tar.begin() + offset, tar.begin() + offset + fileSize);
                files[fileName] = std::move(buffer);
            }
        }

        size_t paddedSize = ((fileSize + 512 - 1) / 512) * 512;
        offset += paddedSize;
    }

    return true;
}

std::optional<FileBuffer> VFS::readFile(const std::string& internalPath) const {
    std::string path = internalPath;
    if (!path.empty() && path[0] == '/') {
        path = path.substr(1);
    }

    auto it = files.find(path);
    if (it != files.end()) return it->second;

    return std::nullopt;
}

bool VFS::hasFile(const std::string& internalPath) const {
    return readFile(internalPath).has_value();
}

std::vector<std::string> VFS::listFiles() const {
    std::vector<std::string> result;
    result.reserve(files.size());

    for (const auto& [path, _] : files) {
        result.push_back(path);
    }

    return result;
}
