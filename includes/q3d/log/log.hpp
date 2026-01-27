#pragma once

#include <string_view>
#include <format>
#include <print>

namespace q3d {
    namespace log {
        template <typename... Args>
        void info(std::string_view fmt, Args&&... message_args) {
            std::println("q3d INFO: {}", 
                std::vformat(fmt, std::make_format_args(std::forward<Args>(message_args)...))
            );
        }

        template <typename... Args>
        void warn(std::string_view fmt, Args&&... message_args) {
            std::println("q3d WARNING: {}", 
                std::vformat(fmt, std::make_format_args(std::forward<Args>(message_args)...))
            );
        }

        template <typename... Args>
        void error(std::string_view fmt, Args&&... message_args) {
            std::println("q3d ERROR: {}!", 
                std::vformat(fmt, std::make_format_args(std::forward<Args>(message_args)...))
            );
        }
    }
}