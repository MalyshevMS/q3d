#pragma once

namespace q3d::gl {

class CubeMap {
private:
    unsigned int cubemap = 0;
    unsigned int fbo = 0;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int count = 0;
public:
    CubeMap(unsigned int resolution, unsigned int count);
    ~CubeMap();

    CubeMap(const CubeMap&) = delete;
    CubeMap& operator=(const CubeMap&) = delete;

    CubeMap(CubeMap&& other) noexcept;
    CubeMap& operator=(CubeMap&& other) noexcept;

    void bindWrite(unsigned int layer) const;

    void bindRead(unsigned int unit = 2) const;

    void clear() const;

    [[nodiscard]] unsigned int getResolution() const { return width; }
    [[nodiscard]] unsigned int getCount() const { return count; }
    [[nodiscard]] unsigned int getTextureId() const { return cubemap; }
};

}
