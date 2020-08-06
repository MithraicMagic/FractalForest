#include <cassert>
#include <iostream>
#include "Buffer.h"

Buffer::Buffer(const std::vector<Vector3> &positions, const std::vector<RGB> &colors) {
    assert(positions.size() == colors.size());
    glGenBuffers(1, &bufferId);

    size = positions.size();

    std::cout << size * sizeof(Vector3) << ", " << size * sizeof(RGB) << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vector3) + size * sizeof(RGB), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(Vector3), &positions[0]);
    glBufferSubData(GL_ARRAY_BUFFER, size * sizeof(Vector3), size * sizeof(RGB), &colors[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::draw() const {
    if (bufferId == 0) {
        return;
    }
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glColorPointer(3, GL_FLOAT, 0, reinterpret_cast<void*>(size * sizeof(Vector3)));

    glDrawArrays(GL_LINES, 0, size);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
