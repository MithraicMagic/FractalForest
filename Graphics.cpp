#include "Graphics.h"
#include "GLBuffer.h"
#include <GL/gl.h>
#include <random>
#include <iostream>
#include <FTGL/ftgl.h>

int ii = 0;

CoinBuffer buildCoin(Vector3 pos, float lineCount = 40) {
    Transformer t;
    std::vector<Vector3> positions;
    std::vector<RGB> colors;

    float scaling = 50.f;
    float thickness = 10.f;
    RGB color = {1, 0.27, 0};

    t.scale({scaling, scaling, scaling});

    //Draw first side of coin
    t.translate({0, 0, thickness/scaling});

    for (int i = 0; i < lineCount; ++i) {
        float a = float(i) / lineCount * 2 * float(M_PI);
        float b = float(i+1) / lineCount * 2 * float(M_PI);

        positions.emplace_back(t.apply({std::cos(a), std::sin(a), 0}));
        positions.emplace_back(t.apply({std::cos(b), std::sin(b), 0}));
        positions.emplace_back(t.apply({std::sin(a), std::cos(a), 0}));
        positions.emplace_back(t.apply({std::cos(b), std::sin(b), 0}));
    }

    //Draw second side of coin
    t.translate({0, 0, -(thickness/scaling*2)});

    for (int i = 0; i < lineCount; ++i) {
        float a = float(i) / lineCount * 2 * float(M_PI);
        float b = float(i+1) / lineCount * 2 * float(M_PI);

        positions.emplace_back(t.apply({std::cos(a), std::sin(a), 0}));
        positions.emplace_back(t.apply({std::cos(b), std::sin(b), 0}));
        positions.emplace_back(t.apply({std::sin(a), std::cos(a), 0}));
        positions.emplace_back(t.apply({std::cos(b), std::sin(b), 0}));
    }

    //Draw lines between coins
    for (int i = 0; i < lineCount; ++i) {
        float a = float(i) / lineCount * 2 * float(M_PI);

        positions.emplace_back(t.apply({std::cos(a), std::sin(a), 0}));

        t.push();
        t.translate({0, 0, (thickness/scaling*2)});

        positions.emplace_back(t.apply({std::cos(a), std::sin(a), 0}));

        t.pop();
    }

    //Fill color vector
    for (int i = 0; float(i) < lineCount*10; ++i) {
        colors.emplace_back(color);
    }

    return CoinBuffer(GLBuffer(positions, colors), pos);
}

//Drawing a squared grid with n*n cells in the x,z-plane, starting at coordinate (0, 0, 0), ending at coordinate (1, 0, 1)
GLBuffer buildGrid(int n) {
    std::vector<Vector3> positions;
    std::vector<RGB> colors;

    for (int i = 0; i <= n; ++i) {
        float pos = float(i) / n;

        for (int j = 0; j < n; ++j) {
            positions.emplace_back(pos, 0, (1.f / n) * j);
            positions.emplace_back(pos, 0, (1.f / n) * (j + 1));

            positions.emplace_back((1.f / n) * j, 0, pos);
            positions.emplace_back((1.f / n) * (j + 1), 0, pos);

            for (int k = 0; k < 4; ++k) {
                colors.push_back({1, 0, 1});
            }
        }
    }

    return GLBuffer(positions, colors);
}

void Graphics::setup() {
    std::uniform_real_distribution<float> treePos(-7500, 7500);
    std::normal_distribution<float> treeSize(0.8, 0.1);

    std::uniform_real_distribution<float> coinPos(-10000, 10000);

    for (int i = 0; i < 100; i++) {
        treeBuffers_.push_back(forest.buildTree({treePos(rng), 0, treePos(rng)}, treeSize(rng), 20.f));
    }

    for (int i = 0; i < 10; ++i) {
        std::uniform_real_distribution<float> angle(0, 1);
        float coinAngle = float(angle(rng)) * M_PI * 2;

        coinBuffers_.emplace_back(buildCoin({std::cos(coinAngle) * coinPos(rng), 200, std::sin(coinAngle) * coinPos(rng)}));
    }

    gridBuffer_ = buildGrid(50);
}

void Graphics::draw(int width, int height, Vector3 cameraPos) {
    std::uniform_real_distribution<float> angle(0, 1);
    std::normal_distribution<float> treeSize(1, 0.05);

    for (TreeBuffer &buffer : treeBuffers_) {
        if (buffer.isInRange(cameraPos, 8500)) {
            buffer.treeBuffer.draw();
        }
        if (!buffer.isInRange(cameraPos, 9000)) {
            float treeAngle = float(angle(rng))*M_PI*2;
            buffer = forest.buildTree({std::cos(treeAngle)*8750-cameraPos.x, 0, std::sin(treeAngle)*8750-cameraPos.z}, treeSize(rng), 20.f);
        }
    }

    for (CoinBuffer &buffer : coinBuffers_) {
        if (buffer.isInRange(cameraPos, 7071)) {
            buffer.draw();
        }

        if (buffer.isInRange(cameraPos, 75.f)) {
            std::cout << "You got a coin!" << std::endl;
            float coinAngle = float(angle(rng)) * M_PI * 2;
            buffer = buildCoin({std::cos(coinAngle) * 4500 - cameraPos.x, 200, std::sin(coinAngle) * 4500 - cameraPos.z});
        }
    }

    int scale = 20000;
    int gridSize = scale/50;
    glTranslatef(std::floor(-cameraPos.x/gridSize)*gridSize, 0, std::floor(-cameraPos.z/gridSize)*gridSize);
    glScalef(scale, 1, scale);
    glTranslatef(-.5f, 0, -.5f);
    gridBuffer_.draw();

//    FTGLPixmapFont font("/usr/share/fonts/truetype/msttcorefonts/ariblk.ttf");
//    glTranslatef(-100, -100, 0);
//    font.FaceSize(100);
//    font.Render(("Score: " + std::to_string(ii++)).c_str(), -1, FTPoint(0, 720));
}