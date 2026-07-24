#pragma once

namespace q3d::gl {

class ShadowMap {
private:
    unsigned int fbo = 0;
    unsigned int depthMap = 0;
    unsigned int width = 2048;
    unsigned int height = 2048;
public:
    ShadowMap(unsigned int res = 2048);
    ~ShadowMap();

    void bindWrite() const;
    void bindRead(unsigned int unit = 1) const;

    unsigned int getDepthMap() const { return depthMap;}
};

} // namespace q3d::gl
