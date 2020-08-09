#ifndef FRACTALFOREST_FOO_H
#define FRACTALFOREST_FOO_H

#include <vector>
#include <cmath>
#include <random>
#include "IDrawable.h"
#include "GLBuffer.h"
#include "Forest.h"

struct CoinBuffer {
    GLBuffer buffer;
    Vector3 position;
    float rotation = 0.f;

    CoinBuffer(GLBuffer buffer, Vector3 pos) : buffer(std::move(buffer)), position(pos) {};

    void draw() {
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glRotatef(rotation, 0, 1, 0);
        buffer.draw();
        glPopMatrix();

        rotation < 360 ? rotation++ : rotation = 0;
    }

    bool isInRange(const Vector3 &other, float range) const {
        float diffX = -other.x - position.x;
        float diffZ = -other.z - position.z;
        return (std::sqrt((diffX*diffX)+(diffZ*diffZ)) < range);
    }
};

class Graphics : public IDrawable {
private:
    std::vector<TreeBuffer> treeBuffers_;
    std::vector<CoinBuffer> coinBuffers_;
    GLBuffer gridBuffer_;

    std::default_random_engine rng;
    Forest forest;
public:
    Graphics() : forest(&rng) {
        std::random_device r;
        rng = std::default_random_engine(r());
    }

    void draw(int width, int height, Vector3 cameraPos) override;

    void setup() override;
};

#endif //FRACTALFOREST_FOO_H
