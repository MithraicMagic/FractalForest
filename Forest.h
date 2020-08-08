#ifndef FRACTALTREE_FOREST_H
#define FRACTALTREE_FOREST_H

#include <random>
#include "Transformer.h"
#include "GLBuffer.h"

struct TreeBuffer {
    Vector3 treePosition;
    GLBuffer treeBuffer;

    bool isInRange(const Vector3 &other, float range) const {
        float diffX = -other.x - treePosition.x;
        float diffZ = -other.z - treePosition.z;
        return (std::sqrt((diffX*diffX)+(diffZ*diffZ)) < range);
    }
};

class Forest {
private:
    std::default_random_engine *rng_;
    std::uniform_real_distribution<float> pitch_;
    std::uniform_real_distribution<float> yaw_;
    Transformer transformer_;
public:
    explicit Forest(std::default_random_engine *rng) : rng_(rng), pitch_(0, 45), yaw_(0, 360) {}

    float randPitch();
    float randYaw();
    TreeBuffer buildTree(Vector3 position, float size, float length, int depth = 10);
    void buildTree(float length, int depth, std::vector<Vector3> *positions, std::vector<RGB> *colors);
};


#endif //FRACTALTREE_FOREST_H
