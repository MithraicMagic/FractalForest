#ifndef FRACTALTREE_TRANSFORMER_H
#define FRACTALTREE_TRANSFORMER_H

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include "Vector3.h"

class Transformer {
private:
    using matrix = boost::numeric::ublas::matrix<float>;
    std::vector<matrix> stack;
    matrix &current() {
        return stack.back();
    }
    const matrix &current() const {
        return stack.back();
    }
public:
    Transformer() {
        stack.push_back(boost::numeric::ublas::identity_matrix<float>(4));
    }

    void push();
    void pop();

    void translate(const Vector3 &v);
    void rotate(float degrees, const Vector3 &v);
    void scale(const Vector3 &v);

    Vector3 apply(const Vector3 &v) const;
};


#endif //FRACTALTREE_TRANSFORMER_H
