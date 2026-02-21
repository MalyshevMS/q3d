#include <q3d/gl/vbo.hpp>

using namespace q3d::gl;
using namespace q3d::gl::buffer;

const Layout Layout::l_xyz_uv = {
    DataType::float3,
    DataType::float2
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

const Layout Layout::l_xyz_rgb_nnn_uv = {
    DataType::float3,
    DataType::float3,
    DataType::float3,
    DataType::float2
};