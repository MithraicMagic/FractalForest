#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class IDrawable
{
public:
	virtual void draw(int width, int height, int seed) = 0;
	virtual ~IDrawable() {}
};

#endif // IDRAWABLE_H
