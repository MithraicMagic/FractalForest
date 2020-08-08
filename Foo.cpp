#include "Foo.h"
#include "GLBuffer.h"
#include <GL/gl.h>
#include <random>
#include <iostream>

//Drawing a squared grid with n*n cells in the x,z-plane, starting at coordinate (0, 0, 0), ending at coordinate (1, 0, 1)
GLBuffer buildGrid(int n) {
    std::vector<Vector3> positions;
    std::vector<RGB> colors;

    for (int i = 0; i <= n; ++i) {
        float pos = float(i) / n;

        for (int j = 0; j < n; ++j) {
            positions.emplace_back(pos, 0, (1.f / n) * j);
            positions.emplace_back(pos, 0, (1.f / n) * (j + 1));

            positions.emplace_back((1.f / n) * j, 0, pos);
            positions.emplace_back((1.f / n) * (j + 1), 0, pos);

            for (int k = 0; k < 4; ++k) {
                colors.push_back({1, 0, 1});
            }
        }
    }

    return GLBuffer(positions, colors);
}

void Foo::setup() {
    std::uniform_real_distribution<float> treePos(-7500, 7500);
    std::normal_distribution<float> treeSize(0.8, 0.1);

    for (int i = 0; i < 100; i++) {
        buffers_.push_back(forest.buildTree({treePos(rng), 0, treePos(rng)}, treeSize(rng), 20.f));
    }

    gridBuffer = buildGrid(50);
}

void Foo::draw(int width, int height, Vector3 cameraPos) {
    std::uniform_real_distribution<float> angle(0, 1);
    std::normal_distribution<float> treeSize(1, 0.05);

    for (TreeBuffer &buffer : buffers_) {
        if (buffer.isInRange(cameraPos, 8500)) {
            buffer.treeBuffer.draw();
        }
        if (!buffer.isInRange(cameraPos, 9000)) {
            float treeAngle = float(angle(rng))*M_PI*2;
            buffer = forest.buildTree({std::cos(treeAngle)*8500-cameraPos.x, 0, std::sin(treeAngle)*8500-cameraPos.z}, treeSize(rng), 20.f);
        }
    }

    int scale = 20000;
    int gridSize = scale/50;
    glTranslatef(std::floor(-cameraPos.x/gridSize)*gridSize, 0, std::floor(-cameraPos.z/gridSize)*gridSize);
    glScalef(scale, 1, scale);
    glTranslatef(-.5f, 0, -.5f);
    gridBuffer.draw();
}