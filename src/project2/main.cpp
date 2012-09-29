#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <vector>

#include "./ball.h"

using namespace std;

// Game state
vector<Ball*> balls;    // A list of balls. The player's is the first

void MakeMap() {
  balls.push_back(new Ball(255, 255, 255));   // cue ball
  balls.push_back(new Ball(255, 0, 0, 50, 50));   // cue ball
}

void Init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);
  glDisable(GL_BLEND);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-400.0, 300.0, -300.0, 400.0);
  glMatrixMode(GL_MODELVIEW);

  MakeMap();
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  for (int i = 0; i < balls.size(); i++) {
    glColor3f(balls[i]->color.r, balls[i]->color.g, balls[i]->color.b);
    glBegin(GL_TRIANGLE_FAN);
    for (int j = 0; j < balls[i]->disk.verts.size(); i++) {
      glVertex2f(balls[i]->disk.verts[j]->x, balls[i]->disk.verts[j]->y);
    }
    glEnd();
  }
  glFlush();
}

void Idle() {
  
}

void Keyboard(unsigned char key, int x, int y) {
  
}

void Mouse(int button, int state, int x, int y) {
  
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
