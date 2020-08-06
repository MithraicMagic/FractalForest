#ifndef FRACTALTREE_BUFFER_H
#define FRACTALTREE_BUFFER_H


#include <cstddef>
#include <vector>
#include <GL/gl.h>
#include "Vector3.h"

struct RGB {
    float r = 1;
    float g = 1;
    float b = 1;
};

class Buffer {
private:
    unsigned int bufferId_ = 0;
    std::size_t size_ = 0;

public:
    Buffer() = default;
    Buffer(const std::vector<Vector3> &positions, const std::vector<RGB> &colors);

    Buffer(const Buffer &) = delete;
    Buffer &operator=(const Buffer &) = delete;

    Buffer(Buffer &&other) noexcept : bufferId_(other.bufferId_), size_(other.size_) {
        other.bufferId_ = 0;
        other.size_ = 0;
    }
    Buffer &operator=(Buffer &&other) {
        Buffer tmp(std::move(other));
        this->~Buffer();
        new(this) Buffer(std::move(tmp));
        return *this;
    }

    ~Buffer() {
        if (bufferId_ != 0) {
            glDeleteBuffers(1, &bufferId_);
        }
    }

    void draw() const;
};

#endif //FRACTALTREE_BUFFER_H
