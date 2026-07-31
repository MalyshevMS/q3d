#pragma once

#include <span>

namespace q3d::gl {

class Ssbo {
private:
    unsigned int id = 0;
    unsigned int binding = 0;
public:
    Ssbo(unsigned int binding);

    ~Ssbo();

    Ssbo(const Ssbo&) = delete;
    Ssbo& operator=(const Ssbo&) = delete;

    Ssbo(Ssbo&& other) noexcept;

    void bind() const;
    static void unbind();
    void bindBase() const;

    void updateData(const void* data, unsigned int size);

    template<class T>
    void updateData(const std::span<T> data) {
        updateData(data.data(), data.size_bytes());
    }
};

} // namespace q3d::gl
