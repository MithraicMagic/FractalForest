#ifndef PLATFORMER_FOO_H
#define PLATFORMER_FOO_H

#include <vector>
#include "IDrawable.h"
#include "GLBuffer.h"

class Foo : public IDrawable {
private:
    std::vector<GLBuffer> buffers_;
    GLBuffer gridBuffer;
public:
    void draw(int width, int height, int seed) override;
    void setup() override;
};


#endif //PLATFORMER_FOO_H
