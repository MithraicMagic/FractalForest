#include "Foo.h"
#include <GL/gl.h>
#include <random>

class Forest {
private:
    std::default_random_engine *rng_;
    std::uniform_real_distribution<float> pitch_;
    std::uniform_real_distribution<float> yaw_;

public:
    explicit Forest(std::default_random_engine *rng) : rng_(rng), pitch_(0, 45), yaw_(0, 360) {}

    float randPitch() {
        return pitch_(*rng_);
    }

    float randYaw() {
        return yaw_(*rng_);
    }

    void drawTree(float length, int depth = 10) {
        glPushMatrix();

        glBegin(GL_LINES);
        glColor3f(1.f / float(depth), 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, length * depth, 0);
        glEnd();

        if (depth > 0) {
            glTranslatef(0, length * depth, 0);

            glPushMatrix();
            glRotatef(randYaw(), 0, 1, 0);
            glRotatef(randPitch(), 0, 0, 1);
            drawTree(length, depth - 1);
            glPopMatrix();

            glRotatef(randYaw(), 0, 1, 0);
            glRotatef(randPitch(), 0, 0, 1);
            drawTree(length, depth - 1);
        }

        glPopMatrix();
    }
};

//Drawing a squared grid with n*n cells in the x,z-plane, starting at coordinate (0, 0, 0), ending at coordinate (1, 0, 1)
void drawGrid(int n) {
    glBegin(GL_LINES);

    for (int i = 0; i <= n; ++i) {
        float pos = float(i)/n;
        glVertex3f(pos, 0, 0);
        glVertex3f(pos, 0, 1);

        glVertex3f(0, 0, pos);
        glVertex3f(1, 0, pos);
    }

    glEnd();
}

void Foo::draw(int width, int height, int seed) {
    std::default_random_engine rng(seed);

    glTranslatef(0, -height / 2, 0);
    Forest forest(&rng);

    std::uniform_real_distribution<float> treepos(-5000, 5000);

    for (int i = 0; i < 15; i++) {
        glPushMatrix();
        glTranslatef(treepos(rng), 0, treepos(rng));
        forest.drawTree(20.f);
        glPopMatrix();
    }

    glScalef(10000, 1, 10000);
    glTranslatef(-.5, 0, -.5);
    drawGrid(50);
}