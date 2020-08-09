#include "Environment.h"
#include "Vector3.h"
#include "GLHelper.h"

#include <GL/glut.h>
#include <cmath>
#include <array>
#include <iostream>

// #define PRINT_DURATION

enum key {
    backspace = 8,
    escape = 27
};

namespace {
    std::array<bool, 26> keyStates{};
    IDrawable *s_drawable;

    Vector3 startingPos = {0, -250, 0};
    Vector3 cameraPos;

    float cameraYaw;
    float cameraPitch;
    float speed = 10;
    float mouseSensitivity = 0.5;

    int s_window_width = 1280;
    int s_window_height = 720;

    void reset() {
        cameraPos = startingPos;
        cameraYaw = 0;
        cameraPitch = 0;
    }

    void reshape(int width, int height) {
        s_window_width = width = (width + 1) / 2 * 2;
        s_window_height = height = (height + 1) / 2 * 2;

        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(75, float(width) / float(height), 0.01, 25000);

        glMatrixMode(GL_MODELVIEW);
    }

    bool isKeyDown(char c) {
        return keyStates[c - 'a'];
    }

    void updatePosition() {
        float tempX = 0.f;
        float tempZ = 0.f;

        if (isKeyDown('w')) {
            tempX += std::sin(cameraYaw / 180.f * float(M_PI));
            tempZ += std::cos(cameraYaw / 180.f * float(M_PI));
        }
        if (isKeyDown('a')) {
            tempX += std::sin((cameraYaw + 90) / 180.f * float(M_PI));
            tempZ += std::cos((cameraYaw + 90) / 180.f * float(M_PI));
        }
        if (isKeyDown('s')) {
            tempX += std::sin((cameraYaw + 180) / 180.f * float(M_PI));
            tempZ += std::cos((cameraYaw + 180) / 180.f * float(M_PI));
        }
        if (isKeyDown('d')) {
            tempX += std::sin((cameraYaw - 90) / 180.f * float(M_PI));
            tempZ += std::cos((cameraYaw - 90) / 180.f * float(M_PI));
        }

        float vectorLength = std::sqrt(tempX * tempX + tempZ * tempZ);

        if (vectorLength > 0.1) {
            cameraPos.x += tempX / vectorLength * speed;
            cameraPos.z += tempZ / vectorLength * speed;
        }
    }

    void display() {
#ifdef PRINT_DURATION
        typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::microseconds microseconds;
    Clock::time_point t0 = Clock::now();
#endif
        updatePosition();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glTranslated(.5, .5, 0);

        glPushMatrix();

        glPushMatrix();
        glRotatef(-cameraPitch, 1, 0, 0);
        glRotatef(-cameraYaw, 0, 1, 0);
        glTranslate(cameraPos);
        s_drawable->draw(s_window_width, s_window_height, cameraPos);
        glPopMatrix();

        glPopMatrix();

        glutSwapBuffers();

#ifdef PRINT_DURATION
        Clock::time_point t1 = Clock::now();
    microseconds us = std::chrono::duration_cast<microseconds>(t1 - t0);
    std::cout << us.count() << " µs\n";
#endif
    }

    void keyboard(unsigned char k, int x, int y) {
        switch (k) {
            case key::backspace:
                reset();
                break;
            case key::escape:
                exit(0);
            case 'r':
                cameraYaw++;
                break;
            case 't':
                cameraYaw--;
                break;
            case 'c':
                cameraPos.y += 10;
                break;
            case ' ':
                cameraPos.y -= 10;
                break;
            default:
                if (k >= 'a' && k <= 'z') {
                    keyStates[k - 'a'] = true;
                }
        }
    }

    void keyboardUp(unsigned char k, int x, int y) {
        if (k >= 'a' && k <= 'z') {
            keyStates[k - 'a'] = false;
        }
    }

    void special(int k, int x, int y) {
        switch (k) {
            case GLUT_KEY_LEFT:
                cameraPos.x++;
                break;
            case GLUT_KEY_UP:
                cameraPos.y--;
                break;
            case GLUT_KEY_RIGHT:
                cameraPos.x--;
                break;
            case GLUT_KEY_DOWN:
                cameraPos.y++;
                break;
            case GLUT_KEY_PAGE_UP:
                cameraPos.x++;
                cameraPos.y--;
                break;
            case GLUT_KEY_PAGE_DOWN:
                cameraPos.x--;
                cameraPos.y++;
                break;
        }
    }

    int s_old_x, s_old_y;

    void mouse(int button, int state, int x, int y) {
        if (state == GLUT_UP) return;

        switch (button) {
            case 3: // scroll up
                break;

            case 4: // scroll down
                break;

            default:
                s_old_x = x;
                s_old_y = y;
        }
    }

    void motion(int x, int y) {
        cameraYaw += mouseSensitivity * (s_old_x - x);
        cameraPitch += mouseSensitivity * (s_old_y - y);

        cameraPitch = clamp(-70.f, cameraPitch, 70.f);

        s_old_x = x;
        s_old_y = y;
    }

    void update(int val) {
        glutPostRedisplay();
        glutTimerFunc(1000 / 60, update, 0);
    }
} // namespace



void Environment2D::init(int &argc, char **argv) {
    glutInit(&argc, argv);
}

void Environment2D::set_drawable(IDrawable *drawable) {
    s_drawable = drawable;
}

void Environment2D::start() {
    reset();

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(s_window_width, s_window_height);
    glutCreateWindow("Fractal Trees");

    glEnable(GL_DEPTH_TEST);

    GLfloat fogColor[4] = {0,0,0,1};
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_START, 3500.0f); // Fog Start Depth
    glFogf(GL_FOG_END, 5000.0f); // Fog End Depth
    glEnable(GL_FOG);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutTimerFunc(1000 / 60, update, 0);

    s_drawable->setup();

    glutMainLoop();
}
