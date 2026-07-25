#pragma once

namespace q3d::gl {

class ShadowMap {
private:
    unsigned int fbo = 0;
    unsigned int depthMap = 0;
    unsigned int width = 2048;
    unsigned int height = 2048;
    unsigned int maxLayers = 512;
public:
    ShadowMap(unsigned int res = 2048, unsigned int layers = 8);
    ~ShadowMap();

    void bindWrite(unsigned int layer) const;
    void bindRead(unsigned int unit = 1) const;

    // unsigned int getDepthMap() const { return depthMap;}
    // unsigned int getMaxLayers() const { return  maxLayers; }
};

} // namespace q3d::gl
