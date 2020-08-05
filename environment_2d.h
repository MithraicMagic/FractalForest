#ifndef ENVIRONMENT_2D_H
#define ENVIRONMENT_2D_H

#include "idrawable.h"

class Environment2D
{
public:
	static void init(int &argc, char **argv);
	static void set_drawable(IDrawable *drawable);
	static void start();
};

#endif // ENVIRONMENT_2D_H
