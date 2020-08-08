#include "Forest.h"
#include "GLBuffer.h"

float Forest::randPitch() {
    return pitch_(*rng_);
}

float Forest::randYaw() {
    return yaw_(*rng_);
}

TreeBuffer Forest::buildTree(Vector3 position, float size, float length, int depth) {
    std::vector<Vector3> positions;
    std::vector<RGB> colors;

    transformer_.push();
    transformer_.translate(position);
    transformer_.scale({size, size, size});
    buildTree(length, depth, &positions, &colors);
    transformer_.pop();

    return TreeBuffer{positions[0], GLBuffer(positions, colors)};
}

void Forest::buildTree(float length, int depth, std::vector<Vector3> *positions, std::vector<RGB> *colors) {
    colors->push_back({1.f / float(depth), 0, 1});
    positions->push_back(transformer_.apply({0, 0, 0}));

    colors->push_back({1.f / float(depth - 1), 0, 1});
    positions->push_back(transformer_.apply({0, length * depth, 0}));

    if (depth > 0) {
        transformer_.translate({0, length * depth, 0});

        transformer_.push();
        transformer_.rotate(randYaw(), {0, 1, 0});
        transformer_.rotate(randPitch(), {0, 0, 1});
        buildTree(length, depth - 1, positions, colors);
        transformer_.pop();

        transformer_.rotate(randYaw(), {0, 1, 0});
        transformer_.rotate(randPitch(), {0, 0, 1});
        buildTree(length, depth - 1, positions, colors);
    }
}