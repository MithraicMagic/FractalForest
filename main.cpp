#include "environment_2d.h"
#include "Foo.h"

int main(int argc, char **argv) {
    Environment2D::init(argc, argv);

    Foo foo;

    Environment2D::set_drawable(&foo);
    Environment2D::start();

    return 0;
}
