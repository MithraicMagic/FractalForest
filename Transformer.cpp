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
    matrix m = boost::qvm::identity_mat<float, 4>();

    A03(m) = v.x;
    A13(m) = v.y;
    A23(m) = v.z;

    current() *= m;
}

void Transformer::rotate(float degrees, const Vector3 &v) {
    matrix m = boost::qvm::identity_mat<float, 4>();

    float s = std::sin(degrees / 180 * float(M_PI));
    float c = std::cos(degrees / 180 * float(M_PI));

    A00(m) = (1 - c) * v.x * v.x + c;
    A01(m) = (1 - c) * v.x * v.y - s * v.z;
    A02(m) = (1 - c) * v.x * v.z + s * v.y;
    A10(m) = (1 - c) * v.x * v.y + s * v.z;
    A11(m) = (1 - c) * v.y * v.y + c;
    A12(m) = (1 - c) * v.y * v.z - s * v.x;
    A20(m) = (1 - c) * v.x * v.z - s * v.y;
    A21(m) = (1 - c) * v.y * v.z + s * v.x;
    A22(m) = (1 - c) * v.z * v.z + c;

    current() *= m;
}

void Transformer::scale(const Vector3 &v) {
    matrix m = boost::qvm::identity_mat<float, 4>();
    A00(m) = v.x;
    A11(m) = v.y;
    A22(m) = v.z;

    current() *= m;
}

Vector3 Transformer::apply(const Vector3 &v) const {
    boost::qvm::vec<float, 4> w;

    w.a[0] = v.x;
    w.a[1] = v.y;
    w.a[2] = v.z;
    w.a[3] = 1.f;

    boost::qvm::vec<float, 4> res = current() * w;

    return Vector3(res.a[0] / res.a[3], res.a[1] / res.a[3], res.a[2] / res.a[3]);
}