#ifndef FRACTALFOREST_FOO_H
#define FRACTALFOREST_FOO_H

#include <vector>
#include <cmath>
#include <random>
#include "IDrawable.h"
#include "GLBuffer.h"
#include "Forest.h"

class Foo : public IDrawable {
private:
    std::vector<TreeBuffer> buffers_;
    GLBuffer gridBuffer;
    std::default_random_engine rng;
    Forest forest;
public:
    Foo() : forest(&rng) {
        std::random_device r;
        rng = std::default_random_engine(r());
    }

    void draw(int width, int height, Vector3 cameraPos) override;
    void setup() override;
};

#endif //FRACTALFOREST_FOO_H
