//
// Created by nick on 05-08-20.
//

#ifndef FRACTALTREE_VECTOR3_H
#define FRACTALTREE_VECTOR3_H


#include <ostream>

class Vector3 {
public:
    float x = 0;
    float y = 0;
    float z = 0;

    Vector3() = default;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v) {
    return out << "<" << v.x << ", " << v.y << ", " << v.z << ">";
}

#endif //FRACTALTREE_VECTOR3_H
