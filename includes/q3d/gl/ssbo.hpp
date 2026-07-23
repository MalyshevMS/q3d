#pragma once

namespace q3d::gl {

class Ssbo {
private:
    unsigned int id = 0;
    unsigned int binding = 0;

public:
    explicit Ssbo(unsigned int binding);

    ~Ssbo();

    Ssbo(const Ssbo&) = delete;
    Ssbo& operator=(const Ssbo&) = delete;

    Ssbo(Ssbo&& other) noexcept;

    void bind() const;
    static void unbind();
    void bindBase() const;

    void updateData(void* data, unsigned int size);
};

} // namespace q3d::gl
