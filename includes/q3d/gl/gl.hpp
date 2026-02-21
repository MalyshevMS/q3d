#pragma once

#include <q3d/core/color.hpp>
#include <q3d/gl/features.hpp>

namespace q3d {
    namespace gl {
        void clear();
        void clearColor(core::Color color);
        void enable(feature feat);
        void disable(feature feat);
    }
}