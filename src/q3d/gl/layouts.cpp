#include <q3d/gl/vbo.hpp>

using namespace q3d;
using namespace gl;
using namespace buffer;

const Layout Layout::l_xyz = {
    DataType::float3
};

const Layout Layout::l_xy_uv = {
    DataType::float2,
    DataType::float2
};

const Layout Layout::l_xyz_uv = {
    DataType::float3,
    DataType::float2
};

const Layout Layout::l_xyzw = {
    DataType::float4
};

const Layout Layout::l_xyz_rgb = {
    DataType::float3,
    DataType::float3
};

const Layout Layout::l_xyz_rgb_uv = {
    DataType::float3,
    DataType::float3,
    DataType::float2
};

const Layout Layout::l_xyz_nnn_uv = {
    DataType::float3,
    DataType::float3,
    DataType::float2
};

const Layout Layout::l_xyz_uv_nnn = {
    DataType::float3,
    DataType::float2,
    DataType::float3,
};

const Layout Layout::l_xyz_rgb_nnn_uv = {
    DataType::float3,
    DataType::float3,
    DataType::float3,
    DataType::float2
};
