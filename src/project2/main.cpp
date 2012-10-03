#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <vector>

#include <ball.h>
#include <core/point.h>
#include <core/transform.h>

using namespace std;

// Game state
Point A, B;
bool clicked = false;
vector<Ball*> balls;    // A list of balls. The player's is the first
float power = 0;

void MakeMap() {
  balls.push_back(new Ball(255, 255, 255));   // cue ball
  balls.push_back(new Ball(255, 0, 0, 50, 50));
}

void Init() {
  glClearColor(0.1, 1.0, 0.1, 1.0);
  glColor3f(1.0, 0.0, 0.0);
  glDisable(GL_BLEND);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-400.0, 400.0, -300.0, 300.0);
  glMatrixMode(GL_MODELVIEW);

  MakeMap();
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  for (int i = 0; i < balls.size(); i++) {
    glColor3f(balls[i]->color.r, balls[i]->color.g, balls[i]->color.b);
    glBegin(GL_TRIANGLE_FAN);
    for (int j = 0; j < balls[i]->disk.verts.size(); j++) {
      glVertex2f(balls[i]->disk.verts[j].x, balls[i]->disk.verts[j].y);
    }
    glEnd();
  }
  glFlush();
}

void Update(int value) {
  Transform t;
  for (int i = 0; i < balls.size(); i++) {
    for (int j = 0; j < balls[i]->disk.verts.size(); j++) {
      t = Translate(balls[i]->psph.Velocity());
      balls[i]->disk.verts[j] = t(balls[i]->disk.verts[j]);
      balls[i]->disk.c = t(balls[i]->disk.c);
      balls[i]->psph.c = t(balls[i]->psph.c);
    }
  }
  glutPostRedisplay();
}

void Idle() {
  glutTimerFunc(1000, Update, 500);
}

void Keyboard(unsigned char key, int x, int y) {}

void Mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    if (!clicked) {
      A = Point(x, -y);
      clicked = true;
    }
    else {
      B = Point(x, -y);
      balls[0]->psph.v = 0.0002 * (B - A);
      cout << balls[0]->psph.Velocity().x;
      cout << balls[0]->psph.Velocity().y;
      cout << balls[0]->psph.Velocity().z;
      clicked = false;
    }
  }
}


int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Billiard of Doom!");
  glutDisplayFunc(Display);
  glutIdleFunc(Idle);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Mouse);
  
  Init();

  // Enter the main drawing loop
  glutMainLoop();
}
