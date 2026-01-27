#include <q3d/log/log.hpp>
#include <format>
#include <print>

template <typename... Args>
void q3d::log::info(std::string_view fmt, Args &&...message_args) {
    std::println("q3d INFO: {}", 
        std::vformat(fmt, std::make_format_args(std::forward<Args>(message_args)...))
    );
}

template <typename... Args>
void q3d::log::warn(std::string_view fmt, Args &&...message_args) {
    std::println("q3d WARNING: {}", 
        std::vformat(fmt, std::make_format_args(std::forward<Args>(message_args)...))
    );
}

template <typename... Args>
void q3d::log::error(std::string_view fmt, Args &&...message_args) {
    std::println("q3d ERROR: {}!", 
        std::vformat(fmt, std::make_format_args(std::forward<Args>(message_args)...))
    );
}
void q3d::log::info(std::string_view message) {
    std::println("q3d INFO: {}", message);
}

void q3d::log::warn(std::string_view message) {
    std::println("q3d WARNING: {}", message);
}

void q3d::log::error(std::string_view message) {
    std::println("q3d ERROR: {}", message);
}
