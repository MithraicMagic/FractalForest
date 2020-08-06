#include "environment_2d.h"
#include "Vector3.h"
#include "GLHelper.h"

#include <GL/glut.h>
#include <iostream>
#include <cmath>

// #define PRINT_DURATION

enum key {
    backspace = 8,
    escape = 27,
};

static IDrawable *s_drawable;

static Vector3 cameraPos;
static float cameraYaw;
static float cameraPitch;
static float speed = 25;

static int s_rng_seed;

static int s_window_width = 800;
static int s_window_height = 800;

static void reset() {
    cameraPos = Vector3(0, 250, -1000);
    cameraYaw = 0;
    cameraPitch = 0;
    s_rng_seed = 0;
}

static void reshape(int width, int height) {
    s_window_width = width = (width + 1) / 2 * 2;
    s_window_height = height = (height + 1) / 2 * 2;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //For 3D-ness
    gluPerspective(80, float(width) / float(height), 0.01, 25000);

    //For 2D-ness
//	gluOrtho2D(- width / 2, width / 2, - height / 2, height / 2);
    glMatrixMode(GL_MODELVIEW);
}

static void display() {
#ifdef PRINT_DURATION
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::microseconds microseconds;
    Clock::time_point t0 = Clock::now();
#endif

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslated(.5, .5, 0);

    glPushMatrix();

    glPushMatrix();
    glRotatef(-cameraPitch, 1, 0, 0);
    glRotatef(-cameraYaw, 0, 1, 0);
    glTranslate(cameraPos);
    s_drawable->draw(s_window_width, s_window_height, s_rng_seed);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();

#ifdef PRINT_DURATION
    Clock::time_point t1 = Clock::now();
    microseconds us = std::chrono::duration_cast<microseconds>(t1 - t0);
    std::cout << us.count() << " µs\n";
#endif
}

static void keyboard(unsigned char k, int x, int y) {
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
        case 'w':
            cameraPos.x += speed * std::sin(cameraYaw / 180.f * float(M_PI));
            cameraPos.z += speed * std::cos(cameraYaw / 180.f * float(M_PI));
            break;
        case 'a':
            cameraPos.x += speed *  std::sin((cameraYaw + 90) / 180.f * float(M_PI));
            cameraPos.z += speed *  std::cos((cameraYaw + 90) / 180.f * float(M_PI));
            break;
        case 's':
            cameraPos.x += speed *  std::sin((cameraYaw + 180) / 180.f * float(M_PI));
            cameraPos.z += speed *  std::cos((cameraYaw + 180) / 180.f * float(M_PI));
            break;
        case 'd':
            cameraPos.x += speed *  std::sin((cameraYaw - 90) / 180.f * float(M_PI));
            cameraPos.z += speed *  std::cos((cameraYaw - 90) / 180.f * float(M_PI));
            break;
        case 'z':
            s_rng_seed++;
            break;
        case 'x':
            s_rng_seed--;
            break;
    }

    glutPostRedisplay();
}

static void special(int k, int x, int y) {
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

    glutPostRedisplay();
}

static int s_old_x, s_old_y;

static void mouse(int button, int state, int x, int y) {
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

    glutPostRedisplay();
}

static void motion(int x, int y) {
    cameraYaw += s_old_x - x;
    cameraPitch += s_old_y - y;

    cameraPitch = clamp(-70.f, cameraPitch, 70.f);

    s_old_x = x;
    s_old_y = y;
    glutPostRedisplay();
}

static void timer(int val) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 30, timer, 0);
}

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutTimerFunc(1000 / 30, timer, 0);

    s_drawable->setup();

    glutMainLoop();
}
