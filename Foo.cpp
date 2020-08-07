#include "Foo.h"
#include "GLBuffer.h"
#include "Transformer.h"
#include <GL/gl.h>
#include <random>

class Forest {
private:
    std::default_random_engine *rng_;
    std::uniform_real_distribution<float> pitch_;
    std::uniform_real_distribution<float> yaw_;
    Transformer transformer_;

public:
    explicit Forest(std::default_random_engine *rng) : rng_(rng), pitch_(0, 45), yaw_(0, 360) {}

    float randPitch() {
        return pitch_(*rng_);
    }

    float randYaw() {
        return yaw_(*rng_);
    }

    GLBuffer buildTree(float length, int depth = 10) {
        std::vector<Vector3> positions;
        std::vector<RGB> colors;

        buildTree(length, depth, &positions, &colors);

        return GLBuffer(positions, colors);
    }

    void buildTree(float length, int depth, std::vector<Vector3> *positions, std::vector<RGB> *colors) {
        transformer_.push();

        glBegin(GL_LINES);
        colors->push_back({1.f / float(depth), 0, 1});
        positions->push_back(transformer_.apply({0, 0, 0}));

        colors->push_back({1.f / float(depth), 0, 1});
        positions->push_back(transformer_.apply({0, length * depth, 0}));
        glEnd();

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

        transformer_.pop();
    }
};

//Drawing a squared grid with n*n cells in the x,z-plane, starting at coordinate (0, 0, 0), ending at coordinate (1, 0, 1)
void drawGrid(int n) {
    glBegin(GL_LINES);

    for (int i = 0; i <= n; ++i) {
        float pos = float(i) / n;
        glVertex3f(pos, 0, 0);
        glVertex3f(pos, 0, 1);

        glVertex3f(0, 0, pos);
        glVertex3f(1, 0, pos);
    }

    glEnd();
}


void Foo::setup() {
    std::default_random_engine rng(4);

    Forest forest(&rng);

    for (int i = 0; i < 100; i++) {
        buffers_.push_back(forest.buildTree(20.f));
    }
}

void Foo::draw(int width, int height, int seed) {
    std::default_random_engine rng(seed);
    std::uniform_real_distribution<float> treePos(-5000, 5000);

    glTranslatef(0, -height / 2, 0);

    for (const GLBuffer &buffer : buffers_) {
        glPushMatrix();
        glTranslatef(treePos(rng), 0, treePos(rng));
        buffer.draw();
        glPopMatrix();
    }

    std::normal_distribution<float> treeHeight(5, 5);
    for (const GLBuffer &buffer : buffers_) {
//        float tHeight = treeHeight(rng);
        glPushMatrix();
        glTranslatef(treePos(rng), 0, treePos(rng));
        glScalef(0.4, 0.4, 0.4);
        buffer.draw();
        glPopMatrix();
    }

    glColor3f(1, 0, 1);
    glScalef(10000, 1, 10000);
    glTranslatef(-.5, 0, -.5);
    drawGrid(50);
}