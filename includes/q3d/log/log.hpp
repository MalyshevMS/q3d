#pragma once

#include <string_view>

namespace q3d {
    namespace log {
        template <typename... Args> inline void info(std::string_view fmt, Args&&... message_args);
        template <typename... Args> inline void warn(std::string_view fmt, Args&&... message_args);
        template <typename... Args> inline void error(std::string_view fmt, Args&&... message_args);
    }
}