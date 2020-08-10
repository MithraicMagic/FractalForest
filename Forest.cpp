#include <iostream>
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

    std::normal_distribution<float> type(0, 1);

    transformer_.push();
    transformer_.translate(position);
    transformer_.scale({size, size, size});

    float treeType = type(*rng_);

    if (treeType <= 0.5) {
        buildTree(length, depth, &positions, &colors);
    } else {
        buildLongTree(4000.f, &positions, &colors);
    }

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

void Forest::buildLongTree(float length, std::vector<Vector3> *positions, std::vector<RGB> *colors) {
    colors->push_back({0.67, 0.33, 0.1});
    positions->push_back(transformer_.apply({0, 0, 0}));

    colors->push_back({0.67, 0.33, 0.1});
    positions->push_back(transformer_.apply({0, length, 0}));

    std::uniform_real_distribution<float> height(length/6, length);
    for (int i = 0; i < 250; ++i) {
        float branchHeight = height(*rng_);
        buildLongTreeBranch(branchHeight, length, positions, colors);
    }
}

void Forest::buildLongTreeBranch(float height, float treeLength, std::vector<Vector3> *positions, std::vector<RGB> *colors) {
    float branchLength = treeLength/height*100;

    transformer_.push();
    transformer_.translate({0, height, 0});
    transformer_.rotate(randYaw(), {0, 1, 0});
    transformer_.rotate(120, {1, 0, 0});

    colors->push_back({0.67, 0.33, 0.1});
    positions->push_back(transformer_.apply({0, 0, 0}));

    colors->push_back({0.33, 0.16, 0.05});
    positions->push_back(transformer_.apply({0, branchLength, 0}));

    for (int i = 10; i < branchLength; i += 50) {
        transformer_.push();
        transformer_.translate({0, float(i), 0});

        transformer_.push();
        transformer_.rotate(65, {0, 0, 1});
        transformer_.rotate(65, {1, 0, 0});

        colors->push_back({0.67, 0.33, 0.1});
        positions->push_back(transformer_.apply({0, 0, 0}));

        colors->push_back({0, 0.5, 0});
        positions->push_back(transformer_.apply({0, branchLength/15, 0}));

        transformer_.pop();
        transformer_.push();
        transformer_.rotate(-65, {0, 0, 1});
        transformer_.rotate(65, {1, 0, 0});

        colors->push_back({0.67, 0.33, 0.1});
        positions->push_back(transformer_.apply({0, 0, 0}));

        colors->push_back({0, 0.5, 0});
        positions->push_back(transformer_.apply({0, branchLength/15, 0}));

        transformer_.pop();
        transformer_.pop();
    }

    transformer_.pop();
}