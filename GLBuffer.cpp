#include <cassert>
#include <iostream>
#include "GLBuffer.h"

GLBuffer::GLBuffer(const std::vector<Vector3> &positions, const std::vector<RGB> &colors) {
    assert(positions.size() == colors.size());
    glGenBuffers(1, &bufferId_);

    size_ = positions.size();

    glBindBuffer(GL_ARRAY_BUFFER, bufferId_);
    glBufferData(GL_ARRAY_BUFFER, size_ * sizeof(Vector3) + size_ * sizeof(RGB), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size_ * sizeof(Vector3), &positions[0]);
    glBufferSubData(GL_ARRAY_BUFFER, size_ * sizeof(Vector3), size_ * sizeof(RGB), &colors[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLBuffer::draw() const {
    if (bufferId_ == 0) {
        return;
    }
    glBindBuffer(GL_ARRAY_BUFFER, bufferId_);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glColorPointer(3, GL_FLOAT, 0, reinterpret_cast<void*>(size_ * sizeof(Vector3)));

    glDrawArrays(GL_LINES, 0, size_);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
