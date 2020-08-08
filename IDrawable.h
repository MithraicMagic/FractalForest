#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include "Vector3.h"

class IDrawable
{
public:
	virtual void draw(int width, int height, Vector3 cameraPos) = 0;
	virtual void setup() = 0;
	virtual ~IDrawable() = default;
};

#endif // IDRAWABLE_H
