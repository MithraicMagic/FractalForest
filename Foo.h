#ifndef PLATFORMER_FOO_H
#define PLATFORMER_FOO_H

#include "idrawable.h"

class Foo : public IDrawable {
public:
    void draw(int width, int height, int seed) override;
    void setup() override;
};


#endif //PLATFORMER_FOO_H
