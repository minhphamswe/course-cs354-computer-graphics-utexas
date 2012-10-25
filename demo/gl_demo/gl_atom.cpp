#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

#include <core/point.h>
#include <core/vector.h>
#include <core/transform.h>

using namespace ishi;

void Init();

// Callback function prototypes
void Display();
void Resize(int w, int h);
void Keyboard(unsigned char c, int x, int y);
void Idle();
void Motion(int x, int y);

Point eye = Point(100, 100, 100);     // position of the camera;
Point at = Point(0, 0, 0);            // focal point of the camera;
Vector up = Vector(0.f, 1.f, 0.f);    // up direction

void Init() {
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // Set the drawing mode
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_LINE);
}

void SetCamera() {
  gluLookAt(eye[0], eye[1], eye[2],
            at[0], at[1], at.x,
            up[0], up[1], up[2]);
}

void SetProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(40.0, 1, 1, 1500);
}

/// Called by Display to draw the floor. Draw a checkerboard floor.
void DrawFloor() {
  // Save the modelling transform state
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Set modelling transform state to origin
  glLoadIdentity();

  int numSquares = 20;  // number of squares on each side
  int squareSize = 10;  // length of the side of each square

  // Draw the floor
  glBegin(GL_QUADS);
  for (int i = -numSquares/2; i < numSquares/2; i++) {
    for (int j = -numSquares/2; j < numSquares/2; j++) {
      // select color
      if ((i + j) % 2 == 0)
        glColor3f(0.f, 0.f, 0.f);   // black
      else
        glColor3f(1.f, 1.f, 1.f);   // white

      glVertex3f(i * squareSize, 0, j * squareSize);
      glVertex3f(i * squareSize, 0, (j+1) * squareSize);
      glVertex3f((i+1) * squareSize, 0, (j+1) * squareSize);
      glVertex3f((i+1) * squareSize, 0, j * squareSize);
    }
  }
  glEnd();

  // Restore the modelling transform state
  glPopMatrix();
}

/// Called to display every frame
void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  SetProjection();
  SetCamera();

  // Draw the floor
  DrawFloor();

  glFlush();
  glutSwapBuffers();
}

void Keyboard(unsigned char c, int x, int y) {
  std::cout << "Key pressed: " << c << std::endl;
  std::cout << eye.x << eye.y << eye.z << std::endl;
  if (c == 'a' || c == 'A')
    eye = Translate(Vector(5, 0, 0))(eye);
  if (c == 'd' || c == 'D')
    eye = Translate(Vector(-5, 0, 0))(eye);
  if (c == 's' || c == 'S')
    eye = Translate(Vector(0, 5, 0))(eye);
  if (c == 'w' || c == 'W')
    eye = Translate(Vector(0, -5, 0))(eye);
  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Atom");
  
  glutDisplayFunc(Display);
//   glutMotionFunc(Motion);
//   glutReshapeFunc(Resize);
  glutKeyboardFunc(Keyboard);
//   glutIdleFunc(Idle);

  Init();

  glutMainLoop();
  return 0;
}