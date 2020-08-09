#include "Environment.h"
#include "Graphics.h"

int main(int argc, char **argv) {
    Environment2D::init(argc, argv);

    Graphics foo;

    Environment2D::set_drawable(&foo);
    Environment2D::start();

    return 0;
}
