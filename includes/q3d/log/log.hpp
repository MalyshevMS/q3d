#pragma once

#include <string_view>

namespace q3d {
    namespace log {
        template <typename... Args> void info(std::string_view fmt, Args&&... message_args);
        template <typename... Args> void warn(std::string_view fmt, Args&&... message_args);
        template <typename... Args> void error(std::string_view fmt, Args&&... message_args);

        void info(std::string_view message);
        void warn(std::string_view message);
        void error(std::string_view message);
    }
}