#include "Transformer.h"

void Transformer::push() {
    //Making a copy of current matrix, since push_back() can possibly invalidate the reference to current()
    matrix tmp = current();
    stack.push_back(std::move(tmp));
}

void Transformer::pop() {
    assert(stack.size() > 1);
    stack.pop_back();
}

void Transformer::translate(const Vector3 &v) {
    matrix m = boost::numeric::ublas::identity_matrix<float>(4);
    m(0, 3) = v.x;
    m(1, 3) = v.y;
    m(2, 3) = v.z;

    current() = prod(current(), m);
}

void Transformer::rotate(float degrees, const Vector3 &v) {
    matrix m = boost::numeric::ublas::identity_matrix<float>(4);

    float s = std::sin(degrees / 180 * float(M_PI));
    float c = std::cos(degrees / 180 * float(M_PI));

    m(0, 0) = (1 - c) * v.x * v.x + c;
    m(0, 1) = (1 - c) * v.x * v.y - s * v.z;
    m(0, 2) = (1 - c) * v.x * v.z + s * v.y;
    m(1, 0) = (1 - c) * v.x * v.y + s * v.z;
    m(1, 1) = (1 - c) * v.y * v.y + c;
    m(1, 2) = (1 - c) * v.y * v.z - s * v.x;
    m(2, 0) = (1 - c) * v.x * v.z - s * v.y;
    m(2, 1) = (1 - c) * v.y * v.z + s * v.x;
    m(2, 2) = (1 - c) * v.z * v.z + c;

    current() = prod(current(), m);
}

void Transformer::scale(const Vector3 &v) {
    matrix m = boost::numeric::ublas::identity_matrix<float>(4);
    m(0, 0) = v.x;
    m(1, 1) = v.y;
    m(2, 2) = v.z;

    current() = prod(current(), m);
}

Vector3 Transformer::apply(const Vector3 &v) const {
    boost::numeric::ublas::vector<float> w(4);

    w(0) = v.x;
    w(1) = v.y;
    w(2) = v.z;
    w(3) = 1.f;

    boost::numeric::ublas::vector<float> res = prod(current(), w);

    return Vector3(res(0) / res(3), res(1) / res(3), res(2) / res(3));
}