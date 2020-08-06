#ifndef FRACTALTREE_GLHELPER_H
#define FRACTALTREE_GLHELPER_H

#include "Vector3.h"
#include <GL/gl.h>
#include <cmath>

inline void glTranslate(const Vector3 &v) {
    glTranslatef(v.x, v.y, v.z);
}

inline void glVertex(const Vector3 &v) {
    glVertex3f(v.x, v.y, v.z);
}

template <typename T>
T clamp(T lower, T x, T upper) {
    return std::min(upper, std::max(lower, x));
}

#endif //FRACTALTREE_GLHELPER_H
