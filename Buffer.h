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
    unsigned int bufferId = 0;
    std::size_t size = 0;
public:
    Buffer() = default;
    Buffer(const std::vector<Vector3> &positions, const std::vector<RGB> &colors);

    Buffer(const Buffer &) = delete;
    Buffer &operator=(const Buffer &) = delete;

    Buffer(Buffer &&other) noexcept : bufferId(other.bufferId), size(other.size) {
        other.bufferId = 0;
        other.size = 0;
    }
    Buffer &operator=(Buffer &&other) {
        Buffer tmp(std::move(other));
        this->~Buffer();
        new(this) Buffer(std::move(tmp));
        return *this;
    }

    ~Buffer() {
        if (bufferId != 0) {
            glDeleteBuffers(1, &bufferId);
        }
    }

    void draw() const;
};

#endif //FRACTALTREE_BUFFER_H
