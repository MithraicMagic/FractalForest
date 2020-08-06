#ifndef FRACTALTREE_GLBUFFER_H
#define FRACTALTREE_GLBUFFER_H


#include <cstddef>
#include <vector>
#include <GL/gl.h>
#include "Vector3.h"

struct RGB {
    float r = 1;
    float g = 1;
    float b = 1;
};

class GLBuffer {
private:
    unsigned int bufferId_ = 0;
    std::size_t size_ = 0;

public:
    GLBuffer() = default;
    GLBuffer(const std::vector<Vector3> &positions, const std::vector<RGB> &colors);

    GLBuffer(const GLBuffer &) = delete;
    GLBuffer &operator=(const GLBuffer &) = delete;

    GLBuffer(GLBuffer &&other) noexcept : bufferId_(other.bufferId_), size_(other.size_) {
        other.bufferId_ = 0;
        other.size_ = 0;
    }
    GLBuffer &operator=(GLBuffer &&other) {
        GLBuffer tmp(std::move(other));
        this->~GLBuffer();
        new(this) GLBuffer(std::move(tmp));
        return *this;
    }

    ~GLBuffer() {
        if (bufferId_ != 0) {
            glDeleteBuffers(1, &bufferId_);
        }
    }

    void draw() const;
};

#endif //FRACTALTREE_GLBUFFER_H
