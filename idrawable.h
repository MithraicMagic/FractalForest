#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class IDrawable
{
public:
	virtual void draw(int width, int height, int seed) = 0;
	virtual void setup() = 0;
	virtual ~IDrawable() = default;
};

#endif // IDRAWABLE_H
